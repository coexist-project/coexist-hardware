#include "routes.h"

void Routes::getWiFis()
{
  String str[8];
  JsonTools jsonTools;

  // Cantidad de WiFis detectadas
  int cantOfNetworks = WiFi.scanNetworks();
  JsonArray networkArray = jsonTools.jsonDocument.to<JsonArray>();

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

  serializeJson(networkArray, jsonTools.buffer);
  server.send(200, "application/json", jsonTools.buffer);
}

void Routes::postConnection()
{
  tools::log("Connecting...");
  String output;
  JsonTools jsonTools;
  String jsonPayload = server.arg("plain"); // Obtén el JSON del cuerpo de la solicitud

  DeserializationError error = deserializeJson(jsonDocument, jsonPayload);
  if (error)
  {
    tools::error("Error al analizar JSON");
    serializeJson(jsonResponse(400, "Formato invalido."), output);
    server.send(200, "application/json", output);
    return;
  }

  const char *_ssid = jsonDocument["ssid"];
  const char *_pswd = jsonDocument["pswd"];

  // HANDLE CONNECTION
  if (sta::init(_ssid, _pswd))
  {
    tools::error("Failed to connect to STA.");
    serializeJson(jsonTools.createResponse(400, "Failed to connect to to STA."), output);
    server.send(200, "application/json", output);
    return;
  }

  flowControl.setEstado(Control::ESTADO_CONNECTED);
  serializeJson(jsonTools.createResponse(200, "Connected to " + String(_ssid), String(_ssid)), output);
  server.send(200, "application/json", output);
}