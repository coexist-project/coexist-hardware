#pragma once

#include <ESP8266mDNS.h>

namespace util {
    /**
     * Serial log error message
     * @param msg Error msg
    */
    void error(const char *);

    /**
     * Serial log message
     * @param msg Log msg
    */
    void log(const char *);

    /**
     * Initialize domain name server
     * @param _dns Domain name
    */
    bool initDns(const char *);
}