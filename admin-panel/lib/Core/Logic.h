#pragma once

#include "Control.h"

class Logic
{
public:
  void estado_setup();
  void estado_accesspoint();
  void estado_connected();
};

extern Logic logic;
