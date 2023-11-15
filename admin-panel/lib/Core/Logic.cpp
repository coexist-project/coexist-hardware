#include "Logic.h"

Logic logic;

void Logic::estado_setup()
{
  tools::log("> SETUP");

  //? Access Point Setup
  bool ap_status = ap.init();
  if (!ap_status)
  {
    tools::error("WiFi no inicializado");
    flowControl.setEstado(Control::ESTADO_ERROR);
    return;
  }
  else
  {
    tools::log("- WiFi inicializado.");
    ap.info();
  }

  flowControl.setEstado(Control::ESTADO_ACCESSPOINT);
  tools::log("> ACCESS_POINT");
}

void Logic::estado_connected()
{
  router.server->handleClient();
  router.dnsServer.processNextRequest();
}