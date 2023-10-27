#pragma once

#include <Arduino.h>

namespace tools
{
    /**
     * Serial log error message
     * @param msg Error msg
     */
    void error(const String);

    /** @param msg Log msg */
    void log(const String);
}