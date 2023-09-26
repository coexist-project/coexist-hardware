#include "webServer.h"
#include "Station.h"

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

    webServer->on("/wificonnect", HTTP_POST,
    []() {
        webServer->sendHeader("Access-Control-Allow-Origin", "*");
        webServer->send(200, "text/plain", sv::handleConnection()); 
    });

    webServer->on("/getCredentials", HTTP_GET,
    []() {
        webServer->sendHeader("Access-Control-Allow-Origin", "*");
        webServer->send(200, "application/json", sv::sendCredentials());
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

String sv::handleConnection() {
    String output;
    String jsonPayload = webServer->arg("plain"); // Obtén el JSON del cuerpo de la solicitud
    StaticJsonDocument<200> doc; // Tamaño del buffer para el JSON

    DeserializationError error = deserializeJson(doc, jsonPayload);
    if (error) {
        Serial.print("Error al analizar JSON");
        return "Error al analizar JSON";
    }

    const char* _ssid = doc["ssid"];
    const char* _pswd = doc["psdw"];

    if (sta::init(_ssid, _pswd)) output = "WiFi connected";
    else output = "ERROR";

    return output;
}

String sv::getCredentials() {
    const string* credentials = sta::info();
    
    String output;
    serializeJson(credentials, output);
    return output;
}

void sv::concurrent()
{
    webServer->handleClient();
}