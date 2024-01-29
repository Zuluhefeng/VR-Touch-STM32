#ifndef _AT_H_
#define _AT_H_

#include <cstdint>
#include "AutoPtr.h"

namespace AT
{
    extern const char* ENDL;
    extern const char* SET_STA_MODE;
    extern const char* SET_TRANSPARENT_MODE;
    extern const char* BEGIN_TRANSPARENT_MODE;
    extern AutoPtrArray<const char> CONNECT_WIFI(const char* ssid, const char* pwd);
    extern AutoPtrArray<const char> CONNECT_TCP(const char* ip, uint16_t port);
}

#endif //!_AT_H_
