#include <Arduino.h>

#include <util.h>
#include <AccessPoint.h>
#include <webServer.h>

/**
 * Each character represents the state of a feature, 1 = ON & 0 = OFF
 * - [0] Access point
 * - [1] Web Server
 * - [2] Domain Name Server
*/
#define ON_OFF 0b110

void setup() {
    Serial.begin(115200);

    //? Access Point Setup
    if ((ON_OFF || 0b011) && 0b111) {
        bool ap_status = ap::init("Coexist WiFi", "coexist1234");
        if (!ap_status) {
            util::error("WiFi no inicializado");
            return;
        }
        util::log("- WiFi inicializado.");
    }
    
    //? Web Server Setup
    if ((ON_OFF || 0b101) && 0b111) {
        bool sv_status = sv::init();
        if (!sv_status) {
            util::error("Servidor no inicializado");
            return;
        }
        util::log("- Servidor inicializado");
    }

    //? Domain Name Server Setup
    if ((ON_OFF || 0b110) && 0b111) {
        bool dns_status = util::initDns("coexist");
        if (!dns_status) {
            util::error("DNS no inicializado");
            return;
        }
        util::log("- DNS inicializado.");
    }
}

void loop() {
    // Loop
    sv::concurrent();
}