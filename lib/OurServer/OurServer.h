#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>  //manejo de archivos en el esp8266

namespace sv{

    void handleAssets(AsyncWebServerRequest *);
    bool InitServerWeb();
    String ScanNetworks();
    String ScanData();
    
}