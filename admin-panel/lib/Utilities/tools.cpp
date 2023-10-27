#include "tools.h"

void tools::error(const String _msg)
{
    String errorMessage = "Error > ";
    errorMessage += _msg;
    Serial.println(errorMessage);
}

void tools::log(const String _msg)
{
    Serial.println(_msg);
}