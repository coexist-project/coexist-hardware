#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>

namespace wf {

    bool InitWifi_AP(const char *, const char *);
    bool InitWifi_STA(const char *, const char *);
    bool InitWifi_AP_STA(const char *, const char *, const char *, const char *);

    void Details();

}