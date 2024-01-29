#ifndef _MCU_H_
#define _MCU_H_

#include "NoneCopyAble.h"

class MCU : private NoneCopyAble
{
public:
    virtual void Setup() = 0;
    virtual void Loop() = 0;
};

#endif //!_MCU_H_
