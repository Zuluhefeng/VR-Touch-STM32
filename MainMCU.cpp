#include <Arduino.h>
#include "MainMCU.h"
#include "Config.h"
#include "AT.h"
#include "Stream.h"
#include "Package.h"

const size_t BUFFER_SIZE = 64;

MainMCU::MainMCU()
    : rocker_(ROCKER_CONFIG::VR_X, ROCKER_CONFIG::VR_Y),
    key_(KEY_CONFIG::KEY_UP_PIN, KEY_CONFIG::KEY_DOWN_PIN),
    serial_(SERIAL_CONFIG::RX, SERIAL_CONFIG::TX),
    networkMCU_(Singleton<NetworkMCU>::Instance(serial_)),
    motorManager_(Singleton<MotorManager>::Instance())
{
}

MainMCU::~MainMCU()
{
}

void MainMCU::Setup()
{
    key_.Setup();
    serial_.Setup(SERIAL_CONFIG::BAUD_RATE);
    networkMCU_.Setup();
    motorManager_.Setup();
}

void MainMCU::Loop()
{
    // send rocker data to server
    if (rocker_.Update())
    {
        OutStream os;
        os << (uint16_t)PACKAGE_CMD::REPORT_ROCKER;
        os.Skip(sizeof(PackageHead::len_));
        os << rocker_;
        uint16_t len = os.Len() - sizeof(PackageHead);
        os.RePosition(sizeof(PackageHead::cmd_));
        os << len;
        serial_.SendN(os.Data(), os.Len());
        serial_.Flush();
    }

    // send key data to server
    if (key_.Scan())
    {
        OutStream os;
        os << (uint16_t)PACKAGE_CMD::REPORT_KEY;
        os.Skip(sizeof(PackageHead::len_));
        os << key_;
        uint16_t len = os.Len() - sizeof(PackageHead);
        os.RePosition(sizeof(PackageHead::cmd_));
        os << len;
        serial_.SendN(os.Data(), os.Len());
        serial_.Flush();
    }

    // recv motor data from server
    if (serial_.Available())
    {
        char buf[BUFFER_SIZE];
        int recvN = serial_.RecvN(buf, sizeof(PackageHead));
        if (recvN == sizeof(PackageHead))
        {
            InStream is(buf);
            // head
            uint16_t cmd;
            uint16_t packLen;
            is >> cmd >> packLen;
            // body
            if (serial_.RecvN(buf + sizeof(PackageHead), (int)packLen) == (int)packLen)
            {
                // exec
                switch (cmd)
                {
                case (uint16_t)PACKAGE_CMD::CHANGE_MOTOR:
                    motorManager_.MatchMotor((const bool*)(buf + sizeof(PackageHead)));
                    break;
                case(uint16_t)PACKAGE_CMD::REPORT_ROCKER: // never reach here
                    break;
                case(uint16_t)PACKAGE_CMD::PING:
                    break;
                default:
                    break;
                }
            }
        }
    }

    // sub loop
    motorManager_.Loop();
    networkMCU_.Loop();
}