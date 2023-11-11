#pragma once

#include <Arduino.h>

namespace tools
{
    /**
     * @brief log error message
     * @param msg Error msg
     */
    void error(const String);

    /**
     * @brief log message
     * @param msg Log msg
     */
    void log(const String);
}