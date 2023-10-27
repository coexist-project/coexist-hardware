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

void route::getHome()
{
  server.client().println("HTTP/1.1 200 OK");
  server.client().println("Content-type:text/html");
  server.client().println();
  server.client().print(responseHTML);
}

void route::getApiRoutes()
{
  String buffer;

  String keys[] = {"msg", "/wifi"};
  String values[] = {homepage, "Get all available WiFis"};

  json::createDoc(keys, values, 2, buffer);
  server.send(200, "application/json", buffer);
}