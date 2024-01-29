#include "Debugger.h"

Debugger::Debugger(const uint32_t rx, const uint32_t tx)
    : HardwareSerial(rx, tx)
{
}

Debugger::~Debugger()
{
}

void Debugger::Setup(uint32_t portRate)
{
    HardwareSerial::begin(portRate);
}

Debugger& Debugger::operator<<(const char* str)
{
    HardwareSerial::print(str);
    return *this;
}
Debugger& Debugger::operator<<(const String& str)
{
    HardwareSerial::print(str);
    return *this;
}

Debugger& Debugger::operator<<(const uint32_t& num)
{
    HardwareSerial::print(num);
    return *this;
}

Debugger& Debugger::operator<<(const uint16_t& num)
{
    HardwareSerial::print(num);
    return *this;
}

Debugger& Debugger::operator<<(const ENDL&)
{
    HardwareSerial::println();
    return *this;
}