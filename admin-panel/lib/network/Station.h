#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>

namespace sta {
    bool init(const char *, const char *);
    void info();
}