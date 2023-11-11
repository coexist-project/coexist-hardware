#include "main.h"

WebServer server(80);

void setup()
{
    Serial.begin(912600);

    flowControl.setEstado(Control::ESTADO_ACCESSPOINT);

    tools::log(" ");
    tools::log(" -- Coexist Hardware -- ");
    tools::log(" ");

    router.setup();
}

void loop()
{

    switch (flowControl.getEstado())
    {
    case Control::ESTADO_SETUP:
        logic.estado_setup();
        break;

    case Control::ESTADO_ACCESSPOINT:
        server.handleClient();
        break;

    case Control::ESTADO_CONNECTED:
        server.handleClient();
        break;
    }
}