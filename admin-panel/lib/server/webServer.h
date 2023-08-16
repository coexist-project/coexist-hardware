#pragma once

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

namespace sv {

    /**
     * Initialize web server
     * @return true if success
    */
    bool init(); //const char *

    /**
     * Scan all available networks
     * @return String in JSON Format
    */
    String scanNetworks();

    /**
     * Keeps web server running on loop()
    */
    void concurrent();
}