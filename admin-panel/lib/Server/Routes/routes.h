#pragma once

#include <WebServer.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#include <Control.h>
#include <jsonTools.h>
#include <tools.h>
#include <Station.h>

#define homepage "Welcome to Coexist Hardware Config API"

class Routes : Router
{
public:
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
