#pragma once

#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <AccessPoint.h>
#include <Router.h>
#include <Control.h>

class Logic
{
public:
  void estado_setup();
  // void estado_accesspoint();
  void estado_connected();
};

extern Logic logic;
