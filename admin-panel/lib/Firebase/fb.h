#ifndef Firebase_H_
#define Firebase_H_

#define API_KEY "AIzaSyCkyvcKwAxb0xI3Lv25TIRmVdwNeQGXKF0"
#define FB_PROJECT_ID "abp-testnet"
#define USER_EMAIL "hardware@coexist.website"
#define USER_PASSWORD "BautiFormiMate"

#include "Arduino.h"
#include "WiFi.h"
#include "Firebase_ESP_Client.h"

#include "tools.h"
#include "estados.h"
#include "fbInstance.h"

String getEstado();

class fb
{
public:
  FirebaseData fbdo;

  fb(){};
  void init();
  void firestoreDataUpdate(String ORG, String id);
};

static fb *FbInstance = new fb();
#endif