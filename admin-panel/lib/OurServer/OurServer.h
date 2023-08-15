#pragma once

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>  //manejo de archivos en el esp8266
#include <ArduinoJson.h>

namespace sv{

    bool InitServerWeb(); //const char *
    String ScanNetworks();
    String ScanData();
    void MainLoop();
    
}