#include "Global.h"
#include "Singleton.h"
#include "Config.h"

using namespace GLOBAL;

// DEBUGGER
template <>
class Singleton<Debugger>
{
public:
    static Debugger& Instance()
    {
        static Debugger instance(DEBUGGER_CONFIG::RX, DEBUGGER_CONFIG::TX);
        return instance;
    }
};

Debugger& GLOBAL::DEBUGGER = Singleton<Debugger>::Instance();

