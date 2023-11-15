#pragma once

#include <jsonTools.h>

typedef String DeviceID;

class Control
{
public:
  enum Estados
  {
    // Initial State
    ESTADO_SETUP,
    // Config State
    ESTADO_ACCESSPOINT,
    // Working State
    ESTADO_CONNECTED,
    // Error States
    ESTADO_ERROR,
  };

  /**
   * @brief global state variable setter
   * @param Estado
   * @return void
   */
  void setEstado(Estados);

  /**
   * @brief Global state variable getter
   * @return Actual state as String
   */
  String getEstadoString();

  /**
   * @brief Global state variable getter
   * @return Actual state var
   */
  Estados getEstado();

  /**
   * @brief Global state variable getter
   * @return Actual state
   */
  JSONResponse getESPStatus();

  Estados estado;

private:
  DeviceID id;
};

extern Control flowControl;