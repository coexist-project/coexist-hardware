#include "router.h"

void router::setup()
{
  server.on("/", HTTP_GET, []() -> void
            { route::getHome(); });
  server.on("/api", HTTP_GET, []() -> void
            { route::getApiRoutes(); });

  server.on("/wifi", HTTP_GET, []() -> void
            { route::getWiFis(); });

  //? Not found
  server.onNotFound([]() -> void
                    { server.send(404, "text/plain", "No handler found for this route."); });
}