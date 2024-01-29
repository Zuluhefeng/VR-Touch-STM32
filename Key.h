#ifndef _KEY_H_
#define _KEY_H_

#include <cstdint>
#include "NoneCopyAble.h"

class OutStream;

class Key :private NoneCopyAble
{
public:
    explicit Key(const uint32_t keyUpPin, const uint32_t keyDownPin);
    ~Key();
    void Setup();
    bool Scan(); // scan key status and save to keyStatus_ if NONE return false

    enum Status
    {
        NONE = 0,
        UP = 1,
        DOWN = 2,
    };

    // trans
    friend OutStream&
        operator<<(OutStream& outStream, const Key& key);

private:
    Status keyStatus_;
    const uint32_t keyUpPin_;
    const uint32_t keyDownPin_;
    uint32_t lastScanTime_;
};

#endif //_KEY_H_
