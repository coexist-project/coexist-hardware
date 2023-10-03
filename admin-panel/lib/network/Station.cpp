#include "Station.h"

bool sta::init(const char * _ssid, const char * _password) {

    if (WiFi.begin(_ssid, _password)) {   
        Serial.println(_ssid);
        Serial.println(_password);
        char i = 0;
        while (WiFi.status() != WL_CONNECTED && i <= 60) delay(500);
        if(WiFi.status() == WL_CONNECTED) return true;
        else return false;
    }
    else return false;
}

String* sta::info() {
    String values[] = { WiFi.psk().c_str() , WiFi.SSID().c_str() };
    return values;
}