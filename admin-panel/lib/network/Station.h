#pragma once

#include "Network.h"

#define STA_TIMEOUT_MS 10000

class STA : public Network
{
private:
  String ssid;
  String password;

public:
  /**
   * @brief Station Instance Constructor
   * @param ssid WiFi SSID to connect
   * @param password WiFi password to connect
   */
  STA(String _ssid, String _password);

  /**
   * @brief Initialize connetion to WiFi
   */
  void init();
  void info();
  void disconnected();
};

extern STA sta;