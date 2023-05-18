#include <Arduino.h>
#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>

#define AP_ssid "Coexist WiFi - Cam"
#define AP_psw "coexist1234"

void handleCapture(void);

WebServer server(80);


void setup() {
  // put your setup code here, to run once:
  esp32cam::Config configuracion;

  configuracion.setPins(esp32cam::pins::AiThinker);
  configuracion.setResolution(esp32cam::Resolution::find(1024, 768));
  configuracion.setJpeg(10);

  esp32cam::Camera.begin(configuracion);

  Serial.begin(115200);

  WiFi.softAP(AP_ssid, AP_psw);
  server.on("/capture.jpeg", handleCapture);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handleCapture(void){
  Serial.printf("Taking a photo");
  std::unique_ptr<esp32cam::Frame> img = esp32cam::capture();

  if ( img == nullptr) {
    Serial.printf("No captured img");
    server.send(404, "text/plain", "no captured img");
    return;
  }

  server.setContentLength(img->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  img->writeTo(client);

}