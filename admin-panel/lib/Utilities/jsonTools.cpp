#include "jsonTools.h"

JsonTools jsonTools;

void JsonTools::createDoc(String *keys, String *values)
{
  if ((sizeof(keys) / sizeof(keys[0])) !=
      (sizeof(values) / sizeof(values[0])))
  {
    tools::error("Wrong quantity of elements on keys or values");
    return;
  }

  jsonDocument.clear();
  buffer.clear();

  short count = (sizeof(keys) / sizeof(keys[0]));

  for (int i = 0; i < count; ++i)
  {
    jsonDocument[keys[i]] = values[i];
  }

  serializeJson(jsonDocument, buffer);
}

JSONResponse JsonTools::createResponse(int status, String msg, String payload)
{
  jsonDocument["status"] = status;
  jsonDocument["msg"] = msg;
  if (payload != "")
    jsonDocument["data"] = payload;

  return jsonDocument;
}