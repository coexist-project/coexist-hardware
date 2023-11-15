#pragma once

#include <WebServer.h>
#include <WiFi.h>
#include <memory> // Include the header for std::unique_ptr
#include <DNSServer.h>
#include "Routes/routes.h"

class Router
{
public:
  std::unique_ptr<WebServer> server;
  DNSServer dnsServer;
  void setup();
};

extern Router router;