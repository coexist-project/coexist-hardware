#include "routes.h"

void route::getWiFis()
{
  String buffer;
  String str[8];

  // Temp. JSON document
  StaticJsonDocument<250> jsonDocument;

  // Cantidad de WiFis detectadas
  int cantOfNetworks = WiFi.scanNetworks();
  JsonArray networkArray = jsonDocument.to<JsonArray>();

  for (int i = 0; i < cantOfNetworks; i++)
  {
    bool nameOfNetworkExists = false;

    for (int j = 0; j < int(networkArray.size()); j++)
    {
      if (networkArray[j]["name"] == WiFi.SSID(i))
      {
        nameOfNetworkExists = true;
        break;
      }
    }

    if (!(nameOfNetworkExists))
    {
      JsonObject networkArr = networkArray.createNestedObject();
      networkArr["name"] = WiFi.SSID(i);
      networkArr["security"] = WiFi.encryptionType(i);
    }
  }

  // serializeJson(networkArray, Serial); // Serializar en una cadena
  serializeJson(networkArray, buffer);
  server.send(200, "application/json", buffer);
}

void route::postConnection()
{
  tools::log("Connecting");
  String output;
  String jsonPayload = server.arg("plain"); // Obtén el JSON del cuerpo de la solicitud
  StaticJsonDocument<250> jsonDocument;

  DeserializationError error = deserializeJson(jsonDocument, jsonPayload);
  if (error)
  {
    tools::error("Error al analizar JSON");
    return;
  }

  const String _ssid = jsonDocument["ssid"];
  const String _pswd = jsonDocument["psdw"];

  // HANDLE CONNECTION

  server.send(200, "text/plain", "CONNECTING");
}

/* HandleCon
String sv::handleConnection() {
    Serial.println("Starting");
    Serial.println("HANDLING CONNECTION!");

    if (sta::init(_ssid, _pswd)) output = "WiFi connected";
    else output = "ERROR";

    Serial.println("Connected !");
    return output;
}
*/