#include "main.h"

WebServer server(80);

void setup()
{
    Serial.begin(912600);
    tools::log(" ");
    tools::log(" -- Coexist Hardware -- ");
    tools::log(" ");

    router::setup();
}

static int flowControl = ESTADO_SETUP;

void loop()
{

    switch (flowControl)
    {
    case ESTADO_SETUP:
        flow::machineSetup(flowControl);
        break;

    case ESTADO_ACCESSPOINT:
        server.handleClient();
        break;
    }
}