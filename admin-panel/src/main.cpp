#include "main.h"

void setup()
{
    Serial.begin(912600);

    flowControl.setEstado(Control::ESTADO_SETUP);

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
        logic.estado_connected();
        break;

    case Control::ESTADO_CONNECTED:
        logic.estado_connected();
        break;
    case Control::ESTADO_ERROR:
        tools::error("Ha ocurrido un error!");
        return;
    }
}