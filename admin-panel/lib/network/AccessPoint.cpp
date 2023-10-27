#include "AccessPoint.h"

bool ap::init(IPAddress apIP, DNSServer &dnsServer, const char *_ssid, const char *_password = NULL)
{
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

    if (WiFi.softAP(_ssid, _password))
    {
        dnsServer.start(53, "*", apIP);
        return true;
    }
    else
        return false;
}

void ap::info()
{
    WiFi.printDiag(Serial);
}