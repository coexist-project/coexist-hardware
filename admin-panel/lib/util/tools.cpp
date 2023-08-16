#include "util.h"

void util::error(const char * _msg) {
    String errorMessage = "Error > ";
    errorMessage += _msg;
    Serial.println(errorMessage);
}

void util::log(const char * _msg) {
    Serial.println(_msg);
}