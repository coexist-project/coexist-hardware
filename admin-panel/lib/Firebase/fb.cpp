#include "fb.h"

FB fb;

void FB::init()
{
  // Assign the project host and api key
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Initialize the library with the Firebase authen and config.
  tools::log("> Setup Firebase");
  Firebase.begin(&config, &auth);
}

void FB::firestoreDataUpdate(String ORG, String id)
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

  content.set("fields/ESTADO/string", flowControl.getEstadoString());

  if (Firebase.Firestore.createDocument(&fbdo, FB_PROJECT_ID, "", docPath.c_str(), content.raw()))
  {
    tools::log(fbdo.payload().c_str());
    return;
  }

  tools::error(fbdo.errorReason());
}