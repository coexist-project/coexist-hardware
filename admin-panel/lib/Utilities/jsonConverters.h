#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

namespace json
{
  void createDoc(String *keys, String *values, int count, String &buffer);
}