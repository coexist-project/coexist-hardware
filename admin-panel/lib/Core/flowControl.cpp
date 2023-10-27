#include "flowControl.h"

IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

void flow::machineSetup(int &state)
{
  tools::log("> SETUP");

  //? Access Point Setup
  bool ap_status = ap::init(apIP, dnsServer, "Coexist WiFi", "");
  if (!ap_status)
    tools::error("WiFi no inicializado");
  else
  {
    tools::log("- WiFi inicializado.");
    ap::info();
  }

  server.begin();
  dnsServer.processNextRequest();

  state = ESTADO_ACCESSPOINT;
  tools::log("> ACCESS_POINT");
}