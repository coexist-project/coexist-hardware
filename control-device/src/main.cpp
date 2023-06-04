#include <Arduino.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <esp32cam.h>
#include <FS.h>
#include <Firebase_ESP_Client.h>
#include <WiFi.h>
//Provide the token generation process info.
#include <addons/TokenHelper.h>


//WiFi connection
#define STA_SSID "Fibertel WiFi792 2.4GHz"
#define STA_PSW "password"

//Firebase info
#define FIREBASE_API_KEY "AIzaSyDySSnWeDl8uWGLcp5w1ZeSEDfhL7ZXNNo"
#define USER_EMAIL_FIREBASE "email@gmail.com"
#define USER_PSW_FIREBASE "password"
#define FIREBASE_BUCKET "fir-testing-abp.appspot.com" // la tiene que ser de gs://([name].appspot.com), solo tiene que ser lo que esta entre los parentesis.
#define PHOTO_PATH_NAME "/data/capture.jpg"

#define AP_ssid "Coexist WiFi - Cam"
#define AP_psw "coexist1234"

void handleCapture(void);

//Define Firebase Data objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig configF;

WebServer server(80);

// Capture Photo and Save it to SPIFFS
void capturePhotoSaveSpiffs() {
  // Take a photo with the camera
  Serial.println("Taking a photo...");
  std::unique_ptr<esp32cam::Frame> frame = esp32cam::capture();

  if (frame == nullptr) {
    Serial.println("Camera capture failed");
    return;
  }
  
  delay(1);
  
  if (Firebase.ready()){
    Serial.print("Uploading picture... \n");
    //MIME type should be valid to avoid the download problem.
    //The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
    if (Firebase.Storage.upload(&fbdo,
          FIREBASE_BUCKET, 
          frame->data(),
          frame->size(),
          PHOTO_PATH_NAME, 
          "image/jpeg")
          ){
        Serial.printf("\nDownload URL: %s\n", fbdo.downloadURL().c_str());
      }
      else{
        Serial.println("Upload failed");
        Serial.println(fbdo.errorReason());
      }
  }
}

void initWiFi(){
  WiFi.begin(STA_SSID, STA_PSW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void initSPIFFS(){
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    ESP.restart();
  }
  else {
    delay(500);
    Serial.println("SPIFFS mounted successfully");
  }
}

void initCamera(){
// Init Camera
  esp32cam::Config config;
  config.setPins(esp32cam::pins::AiThinker);
  config.setResolution(esp32cam::Resolution::find(1024, 768));
  config.setJpeg(10);
  esp32cam::Camera.begin(config);
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  initWiFi();
  initSPIFFS();
  initCamera();

  //Firebase
  // Assign the api key
  configF.api_key = FIREBASE_API_KEY;
  //Assign the user sign in credentials
  auth.user.email = USER_EMAIL_FIREBASE;
  auth.user.password = USER_PSW_FIREBASE;
  //Assign the callback function for the long running token generation task
  configF.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&configF, &auth);
  Firebase.reconnectWiFi(true);

  capturePhotoSaveSpiffs();
}

void loop() {
}