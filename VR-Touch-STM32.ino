#include "MainMCU.h"

MainMCU& mainMCU = Singleton<MainMCU>::Instance();

void setup()
{
    mainMCU.Setup();
}

void loop()
{
    mainMCU.Loop();
}