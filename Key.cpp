#include "Arduino.h"
#include "Key.h"
#include "Stream.h"

const uint32_t KEY_SCAN_INTERVAL = 100;

Key::Key(const uint32_t keyUpPin, const uint32_t keyDownPin)
    :keyDownPin_(keyDownPin), keyUpPin_(keyUpPin), keyStatus_(NONE), lastScanTime_(0)
{
}

Key::~Key()
{
}

void Key::Setup()
{
    pinMode(keyDownPin_, INPUT);
    pinMode(keyUpPin_, INPUT);
}

bool Key::Scan()
{
    uint32_t nowTime = HAL_GetTick();
    if (nowTime - lastScanTime_ < KEY_SCAN_INTERVAL)
        return false;

    lastScanTime_ = nowTime;
    int keyDownStatus_ = digitalRead(keyDownPin_);
    int keyUpStatus_ = digitalRead(keyUpPin_);

    if (keyUpStatus_ == keyDownStatus_)
    {
        keyStatus_ = NONE;
        return false;
    }
    else if (keyDownStatus_ == LOW)
    {
        keyStatus_ = DOWN;
    }
    else
    {
        keyStatus_ = UP;
    }
    return true;
}

OutStream& operator<<(OutStream& outStream, const Key& key)
{
    outStream << (uint8_t)key.keyStatus_;
    return outStream;
}