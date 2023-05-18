#include <Arduino.h>
#include <OurServer.h>
#include <OurWifi.h>
#include <OurMdns.h>
#include <OurWebSocket.h>

#define LOG(x) Serial.print(x)

// const char * html[] PROGMEM = R"rawfile([....])rawfile"

void setup() {
  Serial.begin(115200);

  if (LittleFS.begin())
      Serial.println("File system mounted!");

  if (LittleFS.exists("/index.html"))
  {
      File file = LittleFS.open("/index.html", "r");
      if (!file)
          Serial.println("Error al leer el archivo");
      while (file.available())
      {
          Serial.write(file.read());
      }
      file.close();
  }

  if(ws::InitWebSocketServer()) Serial.printf("WebSocketServer iniciado!");
    else Serial.printf("WebSocketServer no iniciado!");

  if(dns::InitDns("Coexist")) Serial.println("mDNS inicializado.");
    else Serial.println("mDNS no inicializado");

  if(wf::InitWifi_AP("Coexist WiFi", "coexist1234")) Serial.println("WiFi inicializado.");
    else Serial.println("WiFi no inicializado");

  if(sv::InitServerWeb("index.html")) Serial.println("Servidor inicializado.");
    else Serial.println("Servidor no inicializado");
}

void loop() {
  // put your main code here, to run repeatedly:
  ws::HandleWebSocketLoop();
}