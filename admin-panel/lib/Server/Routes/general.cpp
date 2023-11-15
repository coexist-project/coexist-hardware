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
  router.server->send(200, "text/html", responseHTML);
}

void Routes::getApiRoutes()
{
  String keys[] = {"msg", "/wifi", "/status", "/connect"};
  String values[] = {homepage, "Get all available WiFis", "Get ESP connection status", "Send SSID and password to connect ESP"};

  jsonTools.createDoc(keys, values);
  router.server->send(200, "application/json", jsonTools.buffer);
}

void Routes::getESPStatus()
{
  bool connected = flowControl.estado == Control::Estados::ESTADO_CONNECTED;

  String keys[] = {"status", "ssid"};
  String values[] = {
      connected ? "OK" : "AP", connected ? WiFi.SSID() : ""};

  jsonTools.createDoc(keys, values);
  router.server->send(200, "application/json", jsonTools.buffer);
}

void Routes::notFound()
{
  router.server->send(404, "text/plain", "No handler found for this route.");
}