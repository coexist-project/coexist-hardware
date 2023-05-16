#include "OurMdns.h"

bool dns::InitDns(const char * _mdns){
    if(MDNS.begin(_mdns))return true;
        else return false;
}