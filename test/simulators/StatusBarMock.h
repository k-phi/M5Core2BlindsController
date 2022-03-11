#ifndef __STATUSBARMOCK_H__
#define __STATUSBARMOCK_H__

#include "../../src/IStatusBar.h"
#include "gmock/gmock.h"

class StatusBarMock : public IStatusBar {
   public:
    MOCK_METHOD(void, load, (), (override));
    MOCK_METHOD(void, setBatteryLevel, (float batteryLevelInPercent),
                (override));
    MOCK_METHOD(void, setStatusMessage, (const char* message), (override));
    MOCK_METHOD(void, setWiFiConnectionStatus, (bool isConnected), (override));
};

#endif  // __STATUSBARMOCK_H__