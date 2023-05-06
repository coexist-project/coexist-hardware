#include "OurWifi.h"

bool wf::InitWifi_AP(const char * _ssid, const char * _password)
{
    WiFi.mode(WIFI_AP);
    Serial.println();

    if (WiFi.softAP(_ssid, _password)) return true;
        else return false;
}

bool wf::InitWifi_AP_STA(const char * _APssid, const char * _APpassword, const char *_STAssid, const char * _STApassword)
{
    WiFi.mode(WIFI_AP_STA);
    Serial.println();

    if (WiFi.softAP(_APssid, _APpassword) || WiFi.begin(_STAssid, _STApassword)) return true;
        else return false;
}


void Details(){

    Serial.println("WiFi AP created!\n");
    WiFi.printDiag(Serial);
    Serial.print("WiFi_AP IP: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("WiFi_STA IP: ");
    Serial.println(WiFi.localIP());

}
    