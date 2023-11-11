#pragma once

#define API_KEY "AIzaSyCkyvcKwAxb0xI3Lv25TIRmVdwNeQGXKF0"
#define FB_PROJECT_ID "abp-testnet"
#define USER_EMAIL "hardware@coexist.website"
#define USER_PASSWORD "BautiFormiMate"

#include "Arduino.h"
#include "WiFi.h"
#include "Firebase_ESP_Client.h"
#include "tools.h"
#include <Control.h>

class FB
{
private:
  FirebaseAuth auth;
  FirebaseConfig config;
  FirebaseData fbdo;
  FirebaseJson content;

public:
  FB(){};
  void init();
  void firestoreDataUpdate(String ORG, String id);
};

extern FB fb;