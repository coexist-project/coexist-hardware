#pragma once

#include <Arduino.h>
#include <ESP8266mDNS.h>

namespace dns{
    bool InitDns(const char*);
}