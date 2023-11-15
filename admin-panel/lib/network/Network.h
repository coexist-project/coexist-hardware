#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <tools.h>

#define ERROR 0
#define OFF 1
#define STARTING 2
#define ON 3

class Network
{
private:
public:
  int ap_status;
  int sta_status;
};