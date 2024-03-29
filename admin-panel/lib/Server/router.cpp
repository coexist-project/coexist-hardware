#include "router.h"

void router::setup()
{
  server.enableCORS(true);

  server.on("/", HTTP_GET, route::getHome);

  server.on("/status", HTTP_GET, route::getESPStatus);

  server.on("/api", HTTP_GET, route::getApiRoutes);

  server.on("/wifi", HTTP_GET, route::getWiFis);

  server.on("/connect", HTTP_POST, route::postConnection);

  //? Not found
  server.onNotFound([]() -> void
                    { server.send(404, "text/plain", "No handler found for this route."); });
}