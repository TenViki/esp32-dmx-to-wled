#include <WiFi.h>
#include <HTTPClient.h>

void updateLights(String lightUrl, int red, int green, int blue, int dimm)
{
  HTTPClient http;

  String url = lightUrl;

  url.replace("{R}", String(red));
  url.replace("{G}", String(green));
  url.replace("{B}", String(blue));https://www.youtube.com/watch?v=NwJUHZUhifU
  url.replace("{A}", String(dimm));

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0)
  {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
}