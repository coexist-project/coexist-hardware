#include "webServer.h"

#define homepage "Welcome to Coexist Config API\nurls:\n- \"/wifi\" -> returns available WiFi networks."

ESP8266WebServer * webServer = new ESP8266WebServer(80);

StaticJsonDocument<1024> doc;

bool sv::init()
{
    webServer->onNotFound(
    []()
        { webServer->send(400, "text/plain", webServer->uri() + homepage);
    });

    webServer->on("/wifi", HTTP_GET,
    []() {
        webServer->sendHeader("Access-Control-Allow-Origin", "*");
        webServer->send(200, "application/json", sv::scanNetworks()); 
    });

    // Habilitar CORS
    // <- sendHeader("Access-Control-Allow-Origin", "*");
    webServer->begin();
    return true;
}

String sv::scanNetworks()
{
    String str[8];

    int cantOfNetworks = WiFi.scanNetworks();
    JsonArray networkArray = doc.to<JsonArray>();

    for (int i = 0; i < cantOfNetworks; i++)
    {
        bool nameOfNetworkExists = false;

        for (int j = 0; j < int(networkArray.size()); j++) {
            if (networkArray[j]["name"] == WiFi.SSID(i)) {
                nameOfNetworkExists = true;
                break;
            }
        }

        if (!(nameOfNetworkExists)) {
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

void sv::concurrent()
{
    webServer->handleClient();
}