#include "jsonConverters.h"

void json::createDoc(String *keys, String *values, int count, String &buffer)
{
  // Temp. JSON document
  StaticJsonDocument<250> jsonDocument;
  jsonDocument.clear();

  for (int i = 0; i < count; ++i)
  {
    jsonDocument[keys[i]] = values[i];
  }
  serializeJson(jsonDocument, buffer);
}
