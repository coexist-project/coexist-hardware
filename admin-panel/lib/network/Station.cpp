#include "Station.h"

#define STA_TIMEOUT_MS 20000

bool sta::init(const char *_ssid, const char *_password)
{
  // Configura el modo WiFi a AP+STA
  WiFi.mode(WIFI_AP_STA);

  tools::log("Trying connection to:");
  tools::log("- SSID: " + String(_ssid));
  tools::log("- Password " + String(_password));

  // Conéctate a una red WiFi
  WiFi.begin(_ssid, _password);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < STA_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    tools::log("");
    return true;
  }

  tools::log("\nConnected to STA!");
  return false;
}