#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <HardwareSerial.h>
#include "NoneCopyAble.h"
#include "AutoPtr.h"

class Serial : private HardwareSerial, private NoneCopyAble
{

public:
    explicit Serial(const uint32_t rx, const uint32_t tx);
    ~Serial();

    void Setup(uint32_t portRate);
    int Recv(char* buf);                       // none blocking
    int RecvN(char* buf, size_t len);          // blocking
    size_t SendN(const char* buf, size_t len); // blocking
    void ClearRecvBuf();

    void Flush();
    bool Available();
    // Endline empty class
    struct ENDL
    {
    } endl;

    // Overload the << operator
    Serial& operator<<(const char* str);
    Serial& operator<<(const String& str);
    Serial& operator<<(const ENDL&);
    Serial& operator<<(const uint32_t& num);
    Serial& operator<<(const uint16_t& num);

    // more << overload
    template <typename T>
    Serial& operator<<(AutoPtrArray<T> ptr)
    {
        T* p = ptr.Release();
        HardwareSerial::print(p);
        return *this;
    };

    // Overload the >> operator
    Serial& operator>>(uint16_t& num);
    Serial& operator>>(uint32_t& num);
};

#endif //!_SERIAL_H_
