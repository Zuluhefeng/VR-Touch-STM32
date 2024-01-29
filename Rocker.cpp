#include <Arduino.h>
#include "Rocker.h"
#include "Debugger.h"
#include "Serial.h"
#include "Stream.h"

Rocker::Rocker(const uint32_t vrXPin, const uint32_t vrYPin)
    : vrXPin_(vrXPin), vrYPin_(vrYPin),
    xStatus_(NONE), yStatus_(NONE),
    vrXDeg_(0), vrYDeg_(0)
{
}

Rocker::~Rocker()
{
}

const uint32_t DOWN_THRESHOLD = 250;
const uint32_t UP_THRESHOLD = 750;

bool Rocker::Update()
{
    uint32_t vrXDeg = analogRead(vrXPin_);
    uint32_t vrYDeg = analogRead(vrYPin_);
    if (vrXDeg == vrXDeg_ && vrYDeg == vrYDeg_)
        return false;
    else
    {
        vrXDeg_ = vrXDeg;
        vrYDeg_ = vrYDeg;
    }

    Status xStatus = xStatus_;
    Status yStatus = yStatus_;

    if (vrXDeg < DOWN_THRESHOLD)
    {
        xStatus_ = LEFT;
    }
    else if (vrXDeg > UP_THRESHOLD)
    {
        xStatus_ = RIGHT;
    }
    else
    {
        xStatus_ = CENTER;
    }

    if (vrYDeg < DOWN_THRESHOLD)
    {
        yStatus_ = DOWN;
    }
    else if (vrYDeg > UP_THRESHOLD)
    {
        yStatus_ = UP;
    }
    else
    {
        yStatus_ = CENTER;
    }

    if (xStatus == xStatus_ && yStatus == yStatus_)
        return false;

    return true;
}

Debugger& operator<<(Debugger& debugger, const Rocker::Status& status)
{
    switch (status)
    {
    case Rocker::NONE:
        debugger << "NONE";
        break;
    case Rocker::LEFT:
        debugger << "LEFT";
        break;
    case Rocker::CENTER:
        debugger << "CENTER";
        break;
    case Rocker::RIGHT:
        debugger << "RIGHT";
        break;
    case Rocker::UP:
        debugger << "UP";
        break;
    case Rocker::DOWN:
        debugger << "DOWN";
        break;
    default:
        debugger << "UNKNOWN";
        break;
    };
    return debugger;
}

Debugger& operator<<(Debugger& debugger, const Rocker& rocker)
{
    debugger << " X: " << rocker.xStatus_ << ", Y: " << rocker.yStatus_;
    return debugger;
}

Serial& operator<<(Serial& serial, const Rocker::Status& status)
{
    switch (status)
    {
    case Rocker::NONE:
        serial << "NONE";
        break;
    case Rocker::LEFT:
        serial << "LEFT";
        break;
    case Rocker::CENTER:
        serial << "CENTER";
        break;
    case Rocker::RIGHT:
        serial << "RIGHT";
        break;
    case Rocker::UP:
        serial << "UP";
        break;
    case Rocker::DOWN:
        serial << "DOWN";
        break;
    default:
        serial << "UNKNOWN";
        break;
    };
    return serial;
}

Serial& operator<<(Serial& serial, const Rocker& rocker)
{
    serial << " X: " << rocker.xStatus_ << " " << rocker.vrXDeg_
        << " , Y: " << rocker.yStatus_ << " " << rocker.vrYDeg_;
    return serial;
}

OutStream&
operator<<(OutStream& outStream, const Rocker& rocker)
{
    outStream << rocker.vrXDeg_ << rocker.vrYDeg_;
    return outStream;
}