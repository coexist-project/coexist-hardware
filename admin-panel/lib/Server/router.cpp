#include "router.h"
#include "Routes/routes.h"

Router router;

void Router::setup()
{
  Routes routes;

  server.enableCORS(true);

  server.on("/", HTTP_GET, routes.getHome);

  server.on("/status", HTTP_GET, routes.getESPStatus);

  server.on("/api", HTTP_GET, routes.getApiRoutes);

  server.on("/wifi", HTTP_GET, routes.getWiFis);

  server.on("/connect", HTTP_POST, routes.postConnection);

  //? Not found
  server.onNotFound([]() -> void
                    { server.send(404, "text/plain", "No handler found for this route."); });
}