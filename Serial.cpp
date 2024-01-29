#include "Serial.h"

Serial::Serial(const uint32_t rx, const uint32_t tx)
    : HardwareSerial(rx, tx)
{
}

Serial::~Serial()
{
}

void Serial::Setup(uint32_t portRate)
{
    HardwareSerial::begin(portRate);
}

// none blocking
int Serial::Recv(char* buf)
{
    int len = 0;
    while (Available())
    {
        HardwareSerial::readBytes(buf++, 1);
        ++len;
    }
    return len;
}

// blocking
int Serial::RecvN(char* buf, size_t len)
{
    int recvN = 0;
    size_t nLeft = len;
    while (nLeft > 0)
    {
        int n = HardwareSerial::readBytes(buf, nLeft);
        if (n > 0)
        {
            recvN += n;
            nLeft -= n;
            buf += n;
        }
        else
        {
            continue;
        }
    }
    return recvN;
}

// blocking
size_t Serial::SendN(const char* buf, size_t len)
{
    size_t sendN = 0;
    size_t nLeft = len;
    while (nLeft > 0)
    {
        int n = HardwareSerial::write(buf, nLeft);
        if (n > 0)
        {
            sendN += n;
            nLeft -= n;
            buf += n;
        }
        else
        {
            continue;
        }
    }
    return sendN;
}

void Serial::ClearRecvBuf()
{
    int len = 0;
    char tmp;
    while (Available())
    {
        HardwareSerial::readBytes(&tmp, 1);
    }
}

void Serial::Flush()
{
    HardwareSerial::flush();
}

bool Serial::Available()
{
    return HardwareSerial::available();
}

Serial& Serial::operator<<(const char* str)
{
    HardwareSerial::print(str);
    return *this;
}
Serial& Serial::operator<<(const String& str)
{
    HardwareSerial::print(str);
    return *this;
}

Serial& Serial::operator<<(const uint32_t& num)
{
    HardwareSerial::print(num);
    return *this;
}

Serial& Serial::operator<<(const uint16_t& num)
{
    HardwareSerial::print(num);
    return *this;
}

Serial& Serial::operator<<(const ENDL&)
{
    HardwareSerial::println();
    return *this;
}

Serial& Serial::operator>>(uint16_t& num)
{
    char buf[sizeof(uint16_t)];
    RecvN(buf, sizeof(uint16_t));
    num = *((uint16_t*)(buf));
    return *this;
}

Serial& Serial::operator>>(uint32_t& num)
{
    char buf[sizeof(uint32_t)];
    RecvN(buf, sizeof(uint32_t));
    num = *((uint32_t*)(buf));
    return *this;
}
