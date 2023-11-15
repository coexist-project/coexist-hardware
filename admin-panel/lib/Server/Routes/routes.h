#pragma once

#include <WebServer.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#include <Control.h>
#include <jsonTools.h>
#include <tools.h>
#include <Station.h>
#include <Router.h>

#define homepage "Welcome to Coexist Hardware Config API"

class Routes
{
public:
  /* #### Homepage */
  static void getHome();
  /* #### Api Routes View */
  static void getApiRoutes();
  /* #### Available WiFis View */
  static void getWiFis();
  /* #### ESP connection status */
  static void getESPStatus();
  /* #### Connect */
  static void postConnection();

  /* #### Not found */
  static void notFound();
};
