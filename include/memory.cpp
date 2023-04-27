#include <EEPROM.h>
#include <WiFi.h>

IPAddress getIpAdress(int start)
{
  IPAddress ip = IPAddress(
      EEPROM.read(start),
      EEPROM.read(start + 1),
      EEPROM.read(start + 2),
      EEPROM.read(start + 3));
  return ip;
}

void setIpAdress(int start, IPAddress ip)
{
  EEPROM.write(start, ip[0]);
  EEPROM.write(start + 1, ip[1]);
  EEPROM.write(start + 2, ip[2]);
  EEPROM.write(start + 3, ip[3]);

  EEPROM.commit();
}

int getNumber(int address)
{
  return EEPROM.read(address);
}

void setNumber(int address, int number)
{
  EEPROM.write(address, number);
  EEPROM.commit();
}

String getSSID()
{
  String ssid = "";
  for (int i = 14; i < 64; i++)
  {
    char c = EEPROM.read(i);
    if (c == 0)
      break;

    ssid += c;
  }
  return ssid;
}

void setSSID(String ssid)
{
  for (int i = 14; i < 64; i++)
  {
    if (i - 14 < ssid.length())
    {
      EEPROM.write(i, ssid[i - 14]);
    }
    else
    {
      EEPROM.write(i, 0);
    }
  }
  EEPROM.commit();
}

String getPassword()
{
  String password = "";
  for (int i = 64; i < 128; i++)
  {
    char c = EEPROM.read(i);
    if (c == 0)
      break;

    password += c;
  }
  return password;
}

void setPassword(String password)
{
  for (int i = 64; i < 128; i++)
  {
    if (i - 64 < password.length())
    {
      EEPROM.write(i, password[i - 64]);
    }
    else
    {
      EEPROM.write(i, 0);
    }
  }
  EEPROM.commit();
}

String getLightUrl()
{
  String lightUrl = "";
  for (int i = 128; i < 512; i++)
  {
    lightUrl += (char)EEPROM.read(i);
  }
  return lightUrl;
}

void setLightUrl(String lightUrl)
{
  for (int i = 128; i < 512; i++)
  {
    EEPROM.write(i, lightUrl[i - 128]);
  }
  EEPROM.commit();
}