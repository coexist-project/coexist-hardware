#pragma once

#include <DNSServer.h>
#include <WebServer.h>

#include "tools.h"
#include "estados.h"
#include "AccessPoint.h"
#include "gWebServer.h"

// State Machine
namespace flow
{
  void machineSetup(int &state);
}