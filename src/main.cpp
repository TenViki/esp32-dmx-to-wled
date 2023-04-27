
#include <WiFi.h>
#include <HTTPClient.h>
#include <EEPROM.h>
#include <WebServer.h>

#include <Esp.h>

#include <dmx.h>

#include "./lights.cpp"
#include "./server.cpp"
#include "./memory.cpp"

String lightUrl = "http://192.168.1.101/win&R={R}&G={G}&B={B}&TT=0&A={A}";

String header;

// void updateLights(int red, int green, int blue)
// {
//   HTTPClient http;

//   String url = lightUrl;

//   url.replace("{R}", String(red));
//   url.replace("{G}", String(green));
//   url.replace("{B}", String(blue));

//   http.begin(url);
//   int httpCode = http.GET();

//   if (httpCode > 0)
//   {
//     Serial.printf("[HTTP] GET... code: %d\n", httpCode);
//   }
//   else
//   {
//     Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
//   }
// }

#define STATUS_LED 5
#define SWITCH 18

boolean switchState = false;

IPAddress Static_ip;
IPAddress Gateway;
IPAddress Subnet;
String SSID;
String PASSWORD;

TaskHandle_t lightsHandlerTask;
WebServer server(80);

int red = 0;
int green = 0;
int blue = 0;
int dimm = 0;

void lightsHandler(void *parameter)
{
  int lastRed = 0;
  int lastGreen = 0;
  int lastBlue = 0;
  int lastDimm = 0;

  for (;;)
  {
    vTaskDelay(25);
    if (!switchState)
      continue;

    if (lastRed != red || lastGreen != green || lastBlue != blue || lastDimm != dimm)
    {
      lastRed = red;
      lastGreen = green;
      lastBlue = blue;
      lastDimm = dimm;
      updateLights(lightUrl, red, green, blue, dimm);
    }

    dimm = DMX::Read(4);
    red = DMX::Read(1);
    green = DMX::Read(2);
    blue = DMX::Read(3);
  }
}

// HTTP SERVER ROUTES
void handleRoot()
{

  String message = renderPage();

  message.replace("{SSID}", SSID);
  message.replace("{PASSWORD}", PASSWORD);

  message.replace("{IP1}", String(Static_ip[0]));
  message.replace("{IP2}", String(Static_ip[1]));
  message.replace("{IP3}", String(Static_ip[2]));
  message.replace("{IP4}", String(Static_ip[3]));

  message.replace("{GATEWAY1}", String(Gateway[0]));
  message.replace("{GATEWAY2}", String(Gateway[1]));
  message.replace("{GATEWAY3}", String(Gateway[2]));
  message.replace("{GATEWAY4}", String(Gateway[3]));

  message.replace("{SUBNET1}", String(Subnet[0]));
  message.replace("{SUBNET2}", String(Subnet[1]));
  message.replace("{SUBNET3}", String(Subnet[2]));
  message.replace("{SUBNET4}", String(Subnet[3]));

  server.send(200, "text/html", message);
}

void setup()
{
  EEPROM.begin(512);
  Serial.begin(115200);

  Static_ip = getIpAdress(0);
  Gateway = getIpAdress(4);
  Subnet = getIpAdress(8);

  pinMode(STATUS_LED, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);

  SSID = getSSID();
  PASSWORD = getPassword();

  Serial.println("Setting static ip");

  if (!WiFi.config(Static_ip, Gateway, Subnet))
  {
    Serial.println("STA Failed to configure");
  }

  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID.c_str(), PASSWORD.c_str());

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  server.on("/", handleRoot);

  xTaskCreatePinnedToCore(
      lightsHandler,
      "changeLights",
      10000,
      NULL,
      1,
      &lightsHandlerTask,
      0);

  DMX::Initialize(input);
}

int readcycle = 0;

void printRow(int start, int end)
{
  // print indexes
  for (int i = start; i < end; i++)
  {
    if (i < 100)
      Serial.print(" ");
    if (i < 10)
      Serial.print(" ");
    Serial.print(i);
    Serial.print(" ");
  }

  Serial.println();

  for (int i = start; i < end; i++)
  {
    int value = DMX::Read(i);
    if (value < 10)
    {
      Serial.print(" ");
    }
    if (value < 100)
    {
      Serial.print(" ");
    }
    Serial.print(DMX::Read(i));
    Serial.print(" ");
  }

  Serial.println();
  Serial.println();
}

void loop()
{
  server.handleClient();

  if (digitalRead(SWITCH))
    switchState = true;
  else
    switchState = false;

  digitalWrite(STATUS_LED, switchState);
}