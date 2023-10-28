#include "routes.h"

StaticJsonDocument<250> jsonError(int status, String msg)
{
  StaticJsonDocument<250> jsonDocument;

  jsonDocument["status"] = status;
  jsonDocument["msg"] = msg;

  return jsonDocument;
}

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
  tools::log("Connecting...");
  String output;
  String jsonPayload = server.arg("plain"); // Obtén el JSON del cuerpo de la solicitud
  StaticJsonDocument<250> jsonDocument;

  DeserializationError error = deserializeJson(jsonDocument, jsonPayload);
  if (error)
  {
    tools::error("Error al analizar JSON");
    serializeJson(jsonError(400, "Formato invalido."), output);
    server.send(200, "application/json", output);
    return;
  }

  const char *_ssid = jsonDocument["ssid"];
  const char *_pswd = jsonDocument["pswd"];

  // HANDLE CONNECTION
  if (sta::init(_ssid, _pswd))
  {
    tools::error("STA not working");
    serializeJson(jsonError(400, "STA not working."), output);
    server.send(200, "application/json", output);
    return;
  }

  ESTADO = ESTADO_CONNECTED;
  server.send(200, "text/plain", "Connected!");
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