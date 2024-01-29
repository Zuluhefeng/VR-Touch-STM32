#ifndef _MAIN_MCU_H_
#define _MAIN_MCU_H_

#include "Singleton.h"
#include "MCU.h"
#include "Rocker.h"
#include "Serial.h"
#include "NetworkMCU.h"
#include "MotorManager.h"
#include "Key.h"

class MainMCU : public MCU
{
    friend class Singleton<MainMCU>;

private:
    explicit MainMCU();
    ~MainMCU();

public:
    void Setup();
    void Loop();

private:
    Rocker rocker_;
    Key key_;
    Serial serial_;
    NetworkMCU& networkMCU_;
    MotorManager& motorManager_;
};

#endif //!_MAIN_MCU_H_
