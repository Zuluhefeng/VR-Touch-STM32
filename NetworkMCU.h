#ifndef _NETWORK_MCU_H_
#define _NETWORK_MCU_H_

#include "Singleton.h"
#include "MCU.h"

class Serial;

class NetworkMCU : public MCU
{
    friend class Singleton<NetworkMCU>;

private:
    explicit NetworkMCU(Serial& serial);
    ~NetworkMCU();

public:
    void Setup();
    void Loop();
    void Ping();


private:
    Serial& serial_;
    int32_t lastPingTime_;
};

template <>
class Singleton<NetworkMCU>
{
public:
    static NetworkMCU& Instance(Serial& serial_)
    {
        static NetworkMCU instance(serial_);
        return instance;
    }
};

#endif //!_NETWORK_MCU_H_
