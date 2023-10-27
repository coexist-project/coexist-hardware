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

  serializeJson(networkArray, Serial); // Serializar en una cadena
  serializeJson(networkArray, buffer);
  server.send(200, "application/json", buffer);
}