#pragma once

#include <WebServer.h>

class Router
{
public:
  WebServer server;
  void setup();
};

extern Router router;