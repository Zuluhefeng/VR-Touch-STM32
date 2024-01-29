#include "AT.h"
#include "NetworkMCU.h"
#include "Serial.h"
#include "Config.h"
#include "Stream.h"
#include "Package.h"

const int32_t PING_TIME_SPACE = 1000;

NetworkMCU::NetworkMCU(Serial& serial)
    : serial_(serial), lastPingTime_(0)
{
}

NetworkMCU::~NetworkMCU()
{
}

void NetworkMCU::Setup()
{
    delay(2000);
    serial_ << AT::SET_STA_MODE << AT::ENDL;
    serial_.Flush();
    delay(1000);
    serial_ << AT::CONNECT_WIFI(NETWORK_CONFIG::WIFI_SSID, NETWORK_CONFIG::WIFI_PASSWORD)
        << AT::ENDL;
    serial_.Flush();
    delay(10000);
    serial_ << AT::CONNECT_TCP(NETWORK_CONFIG::SERVER_IP, NETWORK_CONFIG::SERVER_PORT)
        << AT::ENDL;
    serial_.Flush();
    delay(2000);
    serial_ << AT::SET_TRANSPARENT_MODE << AT::ENDL;
    delay(2000);
    serial_ << AT::BEGIN_TRANSPARENT_MODE << AT::ENDL;
    delay(1000);
    // clear serial
    serial_.ClearRecvBuf();
}

void NetworkMCU::Loop()
{
    uint32_t nowTime = HAL_GetTick();
    if (nowTime - lastPingTime_ > PING_TIME_SPACE)
    {
        Ping();
        lastPingTime_ = nowTime;
    }
}

void NetworkMCU::Ping()
{
    OutStream os;
    os << (uint16_t)PACKAGE_CMD::PING;
    os << (uint16_t)0;
    serial_.SendN(os.Data(), os.Len());
    serial_.Flush();
}