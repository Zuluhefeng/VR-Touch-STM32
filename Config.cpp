#include "Config.h"

const uint32_t DEBUGGER_CONFIG::BAUD_RATE = 9600;
const uint32_t DEBUGGER_CONFIG::RX = PA10;
const uint32_t DEBUGGER_CONFIG::TX = PA9;

const uint32_t SERIAL_CONFIG::BAUD_RATE = 115200;
const uint32_t SERIAL_CONFIG::RX = PA10;
const uint32_t SERIAL_CONFIG::TX = PA9;

const uint32_t ROCKER_CONFIG::VR_X = PA3;
const uint32_t ROCKER_CONFIG::VR_Y = PA2;

const uint32_t KEY_CONFIG::KEY_UP_PIN = PE3;
const uint32_t KEY_CONFIG::KEY_DOWN_PIN = PE4;

const uint32_t MOTOR_CONFIG::MOTOR_NUM = 5;
const uint32_t MOTOR_CONFIG::MOTOR_HALF_ROUND_TIME = 870;
const uint32_t MOTOR_CONFIG::MOTOR_HALF_ROUND_TIME_MAX = 1200;
const uint32_t MOTOR_CONFIG::MOTOR_PIN[MOTOR_CONFIG::MOTOR_NUM][2] =
{
    {PA6, PA5},
    {PC5, PC4},
    {PD9, PD8},
    {PD11, PD10},
    {PD13, PD12},
};

const char* NETWORK_CONFIG::WIFI_SSID = "Sends_507_2.4G";
const char* NETWORK_CONFIG::WIFI_PASSWORD = "wifi.sends.cc";
const char* NETWORK_CONFIG::SERVER_IP = "10.3.37.246";
const uint16_t NETWORK_CONFIG::SERVER_PORT = 3456;