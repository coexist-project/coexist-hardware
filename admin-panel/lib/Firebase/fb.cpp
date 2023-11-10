#include "fb.h"

String getEstado()
{
  switch (ESTADO)
  {
  case 0:
    return "ESTADO_SETUP";
    break;
  case 1:
    return "ESTADO_ACCESSPOINT";
    break;
  case 2:
    return "ESTADO_CONNECTED";
    break;

  default:
    return "OFF";
    break;
  }
}

void fb::init()
{

  FirebaseAuth auth;
  FirebaseConfig config;
  // Assign the project host and api key
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Initialize the library with the Firebase authen and config.
  tools::log("> Setup Firebase");
  Firebase.begin(&this->config, &this->auth);
}

void fb::firestoreDataUpdate(String ORG, String id)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    tools::error("Trying to access firebase with WiFi disconnected!");
    return;
  }

  if (!Firebase.ready())
  {
    tools::error("Firebase not ready!");
    return;
  }

  String docPath = "ORG/" + ORG + "/devices/" + id;

  FirebaseJson content;

  tools::log(String(ESTADO));
  content.set("fields/ESTADO/string", getEstado());

  if (Firebase.Firestore.createDocument(&fbdo, FB_PROJECT_ID, "", docPath.c_str(), content.raw()))
  {
    tools::log(fbdo.payload().c_str());
    return;
  }

  tools::error(fbdo.errorReason());
}