#include "BlindsControllerApplication.h"
#include "ITestDummy.h"
#include "TestDummyM5Core2.h"

void BlindsControllerApplication::setup()
{
    ITestDummy *dummy = new TestDummyM5Core2();
    dummy->showHellowWorld();
    dummy->~ITestDummy();
}

void BlindsControllerApplication::loop()
{
}