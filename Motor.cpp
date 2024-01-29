#include <Arduino.h>
#include "Motor.h"
#include "Config.h"

Motor::Motor(const uint32_t IA, const uint32_t IB)
    : IA_(IA), IB_(IB), movingTimeCounter_(-1),
    nextCmd_(MotorCmd::NONE), status_(MotorStatus::DOWN)
{
}

Motor::~Motor()
{
}

void Motor::Setup()
{
    pinMode(IA_, OUTPUT);
    pinMode(IB_, OUTPUT);
    Stop();
}

void Motor::Loop()
{
    uint32_t now = HAL_GetTick();
    if (IsMoving())
    {
        if (now - movingTimeCounter_ >= MOTOR_CONFIG::MOTOR_HALF_ROUND_TIME)
            EndMoving();
    }
    else if (
        nextCmd_ != MotorCmd::NONE && nextCmd_ != status_ && now - movingTimeCounter_ > MOTOR_CONFIG::MOTOR_HALF_ROUND_TIME_MAX // 确保反向惯性消失
        )
        BegMoving();
}

bool Motor::IsMoving() const
{
    if (status_ == MotorStatus::UPING || status_ == MotorStatus::DOWNING)
        return true;
    else
        return false;
}

void Motor::BegMoving()
{
    switch (nextCmd_)
    {
    case MotorCmd::UP:
        status_ = MotorStatus::UPING;
        break;
    case MotorCmd::DOWN:
        status_ = MotorStatus::DOWNING;
    default:
        // never reach here
        break;
    }
    nextCmd_ = MotorCmd::NONE;
    movingTimeCounter_ = HAL_GetTick();
    Moving();
}

void Motor::EndMoving()
{
    switch (status_)
    {
    case MotorStatus::UPING:
        status_ = MotorStatus::UP;
        break;
    case MotorStatus::DOWNING:
        status_ = MotorStatus::DOWN;
        break;
    default:
        // never reach here
        break;
    }
    Stop();
}

void Motor::Moving()
{
    switch (status_)
    {
    case MotorStatus::UPING:
        digitalWrite(IA_, HIGH);
        digitalWrite(IB_, LOW);
        break;
    case MotorStatus::DOWNING:
        digitalWrite(IA_, LOW);
        digitalWrite(IB_, HIGH);
        break;
    default:
        // never reach here
        break;
    }
}

void Motor::Stop()
{
    digitalWrite(IA_, LOW);
    digitalWrite(IB_, LOW);
}

bool operator==(const Motor::MotorStatus& status, const Motor::MotorCmd& cmd)
{
    switch (status)
    {
    case Motor::MotorStatus::UP:
        return cmd == Motor::MotorCmd::UP;
    case Motor::MotorStatus::DOWN:
        return cmd == Motor::MotorCmd::DOWN;
    default:
        return false;
    }
}

bool operator!=(const Motor::MotorStatus& status, const Motor::MotorCmd& cmd)
{
    return !(status == cmd);
}

bool operator==(const Motor::MotorCmd& cmd, const Motor::MotorStatus& status)
{
    return status == cmd;
}

bool operator!=(const Motor::MotorCmd& cmd, const Motor::MotorStatus& status)
{
    return status != cmd;
}