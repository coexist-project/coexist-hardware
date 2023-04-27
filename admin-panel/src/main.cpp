#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char * ssid = "Coexist WiFi module";
const char * password = "coexist123";

ESP8266WebServer server(8080);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin();
  WiFi.mode(WIFI_AP);

  WiFi.softAP(ssid, password);

  server.on("/", [](){
    server.send(200, "text/plain", "Hola mundo");
  });
  
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}