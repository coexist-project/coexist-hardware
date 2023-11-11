#include "Logic.h"

Logic logic;

void Logic::estado_setup()
{
  tools::log("> SETUP");

  //? Access Point Setup
  bool ap_status = ap::init("Coexist WiFi", "");
  if (!ap_status)
    tools::error("WiFi no inicializado");
  else
  {
    tools::log("- WiFi inicializado.");
    ap::info();
  }

  server.begin();
  dnsServer.processNextRequest();

  flowControl.setEstado(Control::ESTADO_ACCESSPOINT);
  tools::log("> ACCESS_POINT");
}