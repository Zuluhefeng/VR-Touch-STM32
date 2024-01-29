#ifndef _MOTOR_MANAGER_H_
#define _MOTOR_MANAGER_H_

#include "Singleton.h"
#include "NoneCopyAble.h"
#include "Motor.h"
#include "Config.h"

class MotorManager : private NoneCopyAble
{
    friend class Singleton<MotorManager>;

private:
    MotorManager();
    ~MotorManager();

public:
    void Setup();
    void Loop();

    Motor* GetNthMotor(uint32_t n) const { return motorArrPtr_[n]; };
    void MatchMotor(const bool* data);

private:
    Motor** motorArrPtr_;
};

#endif //!_MOTOR_MANAGER_H_
