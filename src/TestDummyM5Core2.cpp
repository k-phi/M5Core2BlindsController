#include <M5Core2.h>
#include "TestDummyM5Core2.h"

void TestDummyM5Core2::showHellowWorld() {
    M5.begin();
    M5.Lcd.print("Hello World anew.");
}