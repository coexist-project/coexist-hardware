#include "OurServer.h"

ESP8266WebServer * webServer = new ESP8266WebServer(80);

StaticJsonDocument<1024> doc;

bool sv::InitServerWeb() // const char * _index
{
    // webServer->serveStatic("/", LittleFS, "/").setDefaultFile(_index);

    webServer->onNotFound(
    []() {
        webServer->send(400, "text/plain", webServer->uri() + " /wifi -> Redes Wi-Fi disponibles");
    });

    webServer->on("/wifi", 
    []() {
        webServer->send(200, "application/json", sv::ScanNetworks()); 
    });

    

    Serial.println(sv::ScanNetworks());

    /*webServer->on("/assets", HTTP_GET, sv::handleAssets);


    webServer->on("/data", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", sv::ScanData()); });

    */
    webServer->begin();

    return true;
}

void sv::MainLoop()
{
    webServer->handleClient();
}

String sv::ScanData()
{
    Dir dir = LittleFS.openDir("/");

    if (dir.isDirectory())
    {
        File file = dir.openFile("r");
        Serial.print(file.name());
    }
    while (dir.next())
    {
        Serial.println("Name: " + dir.fileName());
        Serial.println("Size: " + dir.fileSize());
    }

    return "Showed dir";
}

String sv::ScanNetworks()
{
    String str[8];

    int cantOfNetworks = WiFi.scanNetworks();
    JsonArray networkArray = doc.to<JsonArray>();
    for (int i = 0; i < cantOfNetworks; i++)
    {
        bool *nameOfNetwork = new bool(false);
        for (String nameNetwork : str)
        {
            if (nameNetwork == WiFi.SSID(i))
            {
                *nameOfNetwork = true;
                break;
            }
        }

        if (!(*nameOfNetwork))
        {    
            JsonObject networkArr = networkArray.createNestedObject();
            networkArr["name"] = WiFi.SSID(i);
            networkArr["security"] = WiFi.getScanInfoByIndex(i)->authmode;
        }
    }
    String output;
    serializeJson(networkArray, Serial); // Serializar en una cadena
    serializeJson(networkArray, output);
    return output;
}