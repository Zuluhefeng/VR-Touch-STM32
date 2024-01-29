#ifndef _ROCKER_H_
#define _ROCKER_H_

#include <cstdint>
#include "NoneCopyAble.h"

class Debugger;
class Serial;
class OutStream;

class Rocker : private NoneCopyAble
{

public:
    explicit Rocker(const uint32_t vrXPin, const uint32_t vrYPin);
    ~Rocker();
    bool Update(); // return true if rocker is changed

    // rocker status
    enum Status
    {
        NONE = 0,
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4,
        CENTER = 5
    };

    Status GetXStatus() const
    {
        return xStatus_;
    }

    Status GetYStatus() const
    {
        return yStatus_;
    }

    // debug
    friend Debugger&
        operator<<(Debugger& debugger, const Rocker& rocker);

    friend Serial&
        operator<<(Serial& serial, const Rocker& rocker);

    // trans
    friend OutStream&
        operator<<(OutStream& outStream, const Rocker& rocker);

private:
    const uint32_t vrXPin_;
    const uint32_t vrYPin_;
    uint32_t vrXDeg_;
    uint32_t vrYDeg_;
    Status xStatus_;
    Status yStatus_;
};

#endif //!_ROCKER_H_
