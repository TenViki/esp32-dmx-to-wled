#include <WiFi.h>
#include <WebServer.h>

String renderPage()
{
  return "<!DOCTYPE html>\
  <html>\
    <head >\
      <meta name =\"viewport\" content=\"width=device-width, initial-scale=1\">\
      <meta charset=\"UTF-8\">\
      <link rel=\"icon\" href=\"data:,\">\
      <title>ESP32 RGB LED</title>\
      <style>\
        form {display:grid;grid-template-columns:auto 1fr;grid-gap:1rem; max-width: 40rem; margin: 0 auto;}\
        h2{grid-column:1/3;text-align:center;}\
        body{font-family:Arial,Helvetica,sans-serif; background-color:#121212; color:#fff}\
        h1{text-align:center;}\
        label{white-space:nowrap;display:flex;align-items:center; color: #ccc;}\
        .ip {display: grid; grid-template-columns:1fr 1fr 1fr 1fr;grid-gap: 1rem;}\
        input{padding: .7rem 1rem; border-radius: .5rem; border: 0; outline: 0; background: #333; color: #fff; width: 100%;box-sizing: border-box; font-size: 1rem;}\
        hr{grid-column:1/3;border:0;border-top:1px solid #444;margin:1rem 0;}\
        .ip input {text-align: center;}\
        button {cursor: pointer; padding: .7rem 1rem; border-radius: .5rem; border: 0; outline: 0; background: #3498db; color: #fff; width: 100%;box-sizing: border-box; font-size: 1rem;}\
      </style>\
    </head>\
    <body>\
      <h1>ESP32 DMX Převodník</h1>\
      <form method=\"POST\" action=\"/\">\
        <h2>WiFi nastavení</h2>\
        <label for=\"ssid\">SSID</label>\
        <input type=\"text\" id=\"ssid\" name=\"ssid\" value=\"{SSID}\">\
        <label for=\"password\">Heslo</label>\
        <input type=\"password\" id=\"password\" name=\"password\" value=\"{PASSWORD}\">\
        <hr>\
        <label for=\"ssid\">Statická IP</label>\
        <div class=\"ip\">\
          <input type=\"number\" id=\"ip1\" name=\"ip1\" value=\"{IP1}\" width=\"0\">\
          <input type=\"number\" id=\"ip2\" name=\"ip2\" value=\"{IP2}\" width=\"0\">\
          <input type=\"number\" id=\"ip3\" name=\"ip3\" value=\"{IP3}\" width=\"0\">\
          <input type=\"number\" id=\"ip4\" name=\"ip4\" value=\"{IP4}\" width=\"0\">\
        </div>\
        <label for=\"gateway\">Brána</label>\
        <div class=\"ip\">\
          <input type=\"number\" id=\"gateway1\" name=\"gateway1\" value=\"{GATEWAY1}\" width=\"0\">\
          <input type=\"number\" id=\"gateway2\" name=\"gateway2\" value=\"{GATEWAY2}\" width=\"0\">\
          <input type=\"number\" id=\"gateway3\" name=\"gateway3\" value=\"{GATEWAY3}\" width=\"0\">\
          <input type=\"number\" id=\"gateway4\" name=\"gateway4\" value=\"{GATEWAY4}\" width=\"0\">\
        </div>\
        <label for=\"subnet\">Maska sítě</label>\
        <div class=\"ip\">\
          <input type=\"number\" id=\"subnet1\" name=\"subnet1\" value=\"{SUBNET1}\" width=\"0\">\
          <input type=\"number\" id=\"subnet2\" name=\"subnet2\" value=\"{SUBNET2}\" width=\"0\">\
          <input type=\"number\" id=\"subnet3\" name=\"subnet3\" value=\"{SUBNET3}\" width=\"0\">\
          <input type=\"number\" id=\"subnet4\" name=\"subnet4\" value=\"{SUBNET4}\" width=\"0\">\
        </div>\
\
        <button type =\"submit\">Uložit</button>\
      </form>\
    </body>\
  </html>";
}