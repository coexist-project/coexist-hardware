#include "AccessPoint.h"

bool ap::init(const char * _ssid, const char * _password) {
    WiFi.mode(WIFI_AP);

    if (WiFi.softAP(_ssid, _password)) return true;
    else return false;
}

void ap::info() {
    Serial.println("WiFi AP created!\n");
    WiFi.printDiag(Serial);
}