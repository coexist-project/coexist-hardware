#pragma once

#include <Arduino.h>
#include <tools.h>
#include <WiFi.h>
#include <DNSServer.h>

namespace ap
{
    /**
     * Init Access Point (AP) WiFi.
     * @param IPAddr Access IP
     * @param DNSServer Reference to DNSServer instance
     * @param _ssid WiFi Access Point SSID
     * @param _pswd WiFi Access Point password
     * @return
     */
    bool init(IPAddress, DNSServer &dnsServer, const char *, const char *);

    /**
     * Prints Access Point details.
     */
    void info();
}