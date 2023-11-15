#include "router.h"

Router router;

void Router::setup()
{
  server = std::unique_ptr<WebServer>(new WebServer(80));

  router.server->enableCORS(true);

  router.server->on("/", HTTP_GET, Routes::getHome);

  router.server->on("/status", HTTP_GET, Routes::getESPStatus);

  router.server->on("/api", HTTP_GET, Routes::getApiRoutes);

  router.server->on("/wifi", HTTP_GET, Routes::getWiFis);

  router.server->on("/connect", HTTP_POST, Routes::postConnection);

  //? Not found
  router.server->onNotFound(Routes::notFound);

  tools::log("Setup OK!");
}