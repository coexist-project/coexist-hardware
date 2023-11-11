#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include "tools.h"

typedef StaticJsonDocument<250> JSONResponse;

class JsonTools
{
private:
public:
  JSONResponse jsonDocument;
  String buffer;

  /**
   * @brief Create JSON with keys and values arrays
   * @param keys list
   * @param values list
   */
  void createDoc(String *keys, String *values);

  /**
   * @brief Create standard JSON response
   * @param status Status code
   * @param msg Text msg
   * @param paylaod (optional) Response payload
   */
  JSONResponse createResponse(int status, String msg, String payload = "");
};

extern JsonTools jsonTools;