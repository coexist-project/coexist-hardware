#pragma once

#include <WebServer.h>
#include <ArduinoJson.h>

#include "gWebServer.h"
#include "jsonConverters.h"
#include "tools.h"

#define homepage "Welcome to Coexist Hardware Config API"

namespace route
{
  void getHome();
  void getApiRoutes();
  void getWiFis();
  void postConnection();
}
