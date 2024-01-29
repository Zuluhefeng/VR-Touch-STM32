#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#include <HardwareSerial.h>
#include "NoneCopyAble.h"
#include "Singleton.h"

class Debugger : private HardwareSerial, private NoneCopyAble
{
    friend class Singleton<Debugger>;

private:
    explicit Debugger(const uint32_t rx, const uint32_t tx);
    ~Debugger();

public:
    void Setup(uint32_t portRate);

    // Endline empty class
    struct ENDL
    {
    } endl;
    // Overload the << operator
    Debugger& operator<<(const char* str);
    Debugger& operator<<(const String& str);
    Debugger& operator<<(const ENDL&);
    Debugger& operator<<(const uint32_t& num);
    Debugger& operator<<(const uint16_t& num);
};

#endif //!_DEBUGGER_H_
