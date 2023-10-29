#pragma once

#include <WebServer.h>
#include <ArduinoJson.h>

#include "gWebServer.h"
#include "estados.h"
#include "jsonConverters.h"
#include "tools.h"
#include "Station.h"

#define homepage "Welcome to Coexist Hardware Config API"

namespace route
{
  /* #### Homepage */
  void getHome();
  /* #### Api Routes View */
  void getApiRoutes();
  /* #### Available WiFis View */
  void getWiFis();
  /* #### ESP connection status */
  void getESPStatus();
  /* #### Connect */
  void postConnection();
}
