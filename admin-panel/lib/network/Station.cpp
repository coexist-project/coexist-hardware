#include "Station.h"

STA sta;

STA::STA(String _ssid, String _password)
{
  ssid = _ssid;
  password = _password;
  sta_status = OFF;
}

bool STA::init()
{
  sta_status = STARTING;
  WiFi.mode(WIFI_AP_STA);

  tools::log("Trying connection to:");
  tools::log("- SSID: " + ssid);
  tools::log("- Password " + password);

  // Conéctate a una red WiFi
  WiFi.begin(ssid.c_str(), password.c_str());

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < STA_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(200);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    tools::log("");
    tools::error("Failed to connect to the network!");
    sta_status = ERROR;
    return true;
  }

  tools::log("\nConnected to STA!");
  sta_status = ON;
  return false;
}