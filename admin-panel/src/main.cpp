#include <Arduino.h>
#include <OurServer.h>
#include <OurWifi.h>
#include <OurMdns.h>

#define LOG(x) Serial.print(x)

// const char * html[] PROGMEM = R"rawfile([....])rawfile"

void setup() {
  Serial.begin(115200);
  Serial.println("Inicio");
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

  if(dns::InitDns("Coexist")) Serial.println("mDNS inicializado.");
    else Serial.println("mDNS no inicializado");

  if(wf::InitWifi_AP("CoexistAP", "hola1234")) Serial.println("WiFi inicializado.");
  else Serial.println("WiFi no inicializado");

  if(!sv::InitServerWeb()) Serial.println("Servidor no inicializado");
  else Serial.println("Servidor inicializado");
}

void loop() {
  // put your main code here, to run repeatedly:
  sv::MainLoop();
}