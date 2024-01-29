#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino.h>

namespace DEBUGGER_CONFIG
{
    extern const uint32_t BAUD_RATE;
    extern const uint32_t RX;
    extern const uint32_t TX;
}

namespace SERIAL_CONFIG
{
    extern const uint32_t BAUD_RATE;
    extern const uint32_t RX;
    extern const uint32_t TX;
}

namespace ROCKER_CONFIG
{
    extern const uint32_t VR_X;
    extern const uint32_t VR_Y;
}

namespace KEY_CONFIG
{
    extern const uint32_t KEY_UP_PIN;
    extern const uint32_t KEY_DOWN_PIN;
}

namespace MOTOR_CONFIG
{
    extern const uint32_t MOTOR_NUM;
    extern const uint32_t MOTOR_HALF_ROUND_TIME;
    extern const uint32_t MOTOR_HALF_ROUND_TIME_MAX;
    extern const uint32_t MOTOR_PIN[][2];

}

namespace NETWORK_CONFIG
{
    extern const char* WIFI_SSID;
    extern const char* WIFI_PASSWORD;
    extern const char* SERVER_IP;
    extern const uint16_t SERVER_PORT;
}

#endif //!_CONFIG_H_
