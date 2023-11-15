#include "Control.h"

Control flowControl;

String Control::getEstadoString()
{
  switch (estado)
  {
  case 0:
    return "Access Point Mode";
    break;

  case 1:
    return "Station Mode";

  case 2:
    return "Running Mode";
    break;

  default:
    return "";
    break;
  }
}

Control::Estados Control::getEstado()
{
  return estado;
}

void Control::setEstado(Estados e)
{
  estado = e;
}

JSONResponse Control::getESPStatus()
{
}
