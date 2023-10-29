#include "main.h"

WebServer server(80);
int ESTADO = ESTADO_SETUP;

void setup()
{
    Serial.begin(912600);
    tools::log(" ");
    tools::log(" -- Coexist Hardware -- ");
    tools::log(" ");

    router::setup();
}

void loop()
{

    switch (ESTADO)
    {
    case ESTADO_SETUP:
        flow::machineSetup();
        break;

    case ESTADO_ACCESSPOINT:
        server.handleClient();
        break;

    case ESTADO_CONNECTED:
        server.handleClient();
        break;
    }
}