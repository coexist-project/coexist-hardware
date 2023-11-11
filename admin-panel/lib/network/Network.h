#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <tools.h>

#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#elif __has_include(<WiFiNINA.h>)
#include <WiFiNINA.h>
#elif __has_include(<WiFi101.h>)
#include <WiFi101.h>
#elif __has_include(<WiFiS3.h>)
#include <WiFiS3.h>
#endif

#define ERROR 0
#define OFF 1
#define STARTING 2
#define ON 3

class Network
{
private:
  DNSServer dns_server;

public:
  int ap_status;
  int sta_status;

  /**
   * @brief DNS Server getter
   * @return DNSServer instance
   */
  DNSServer getDNS();
};