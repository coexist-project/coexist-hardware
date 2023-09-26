#include "util.h"

bool util::initDns(const char * _dns) {
    return !!MDNS.begin(_dns);
}