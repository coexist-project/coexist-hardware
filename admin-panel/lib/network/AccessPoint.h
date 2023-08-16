#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>

namespace ap {
    /**
     * Init Access Point (AP) WiFi.
     * @param _ssid WiFi Access Point SSID
     * @param _pswd WiFi Access Point password
     * @return 
     * 
    */
    bool init(const char *, const char *);

    /**
     * Prints Access Point details.
    */
    void info();
}