#include "routes.h"

String responseHTML = "<!DOCTYPE html>"
                      "<html>"
                      "<head>"
                      "<title>Coexist Hardware</title>"
                      "</head>"
                      "<body>"
                      "<h1>Bienvenido al Centro de Configuracion de Coexist Hardware!</h1>"
                      "<p>Haz click <a href='./api'>aqui</a> para ver la API</p>"
                      "</body>"
                      "</html>";

void Routes::getHome()
{
  server.send(200, "text/html", responseHTML);
}

void Routes::getApiRoutes()
{
  String keys[] = {"msg", "/wifi", "/status", "/connect"};
  String values[] = {homepage, "Get all available WiFis", "Get ESP connection status", "Send SSID and password to connect ESP"};

  JsonTools::createDoc(keys, values);
  server.send(200, "application/json", JsonTools::buffer);
}

void Routes::getESPStatus()
{
  bool connected = flowControl.estado == Estados::ESTADO_CONNECTED;

  String keys[] = {"status", "ssid"};
  String values[] = {
      connected ? "OK" : "AP", connected ? WiFi.SSID() : ""};

  json::createDoc(keys, values);
  server.send(200, "application/json", JsonTools::buffer);
}