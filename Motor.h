#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <cstdint>
#include "Singleton.h"
#include "NoneCopyAble.h"

class Motor : NoneCopyAble
{
public:
    explicit Motor(const uint32_t IA, const uint32_t IB);
    ~Motor();
    void Setup();
    void Loop();
    void Up() { nextCmd_ = MotorCmd::UP; };
    void Down() { nextCmd_ = MotorCmd::DOWN; };
    bool IsMoving() const;

    enum class MotorStatus
    {
        UP,
        DOWN,
        UPING,
        DOWNING
    };
    MotorStatus GetStatus() const { return status_; }

private:
    enum class MotorCmd
    {
        UP,
        DOWN,
        NONE
    };
    friend bool operator==(const Motor::MotorStatus& status, const Motor::MotorCmd& cmd);
    friend bool operator!=(const Motor::MotorStatus& status, const Motor::MotorCmd& cmd);
    friend bool operator==(const Motor::MotorCmd& cmd, const Motor::MotorStatus& status);
    friend bool operator!=(const Motor::MotorCmd& cmd, const Motor::MotorStatus& status);

    const uint32_t IA_;
    const uint32_t IB_;
    int32_t movingTimeCounter_;
    MotorCmd nextCmd_;
    MotorStatus status_;

    void BegMoving();
    void EndMoving();
    void Moving();
    void Stop();
};

#endif //!_MOTOR_H_
