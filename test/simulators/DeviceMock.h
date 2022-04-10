#ifndef __DEVICEMOCK_H__
#define __DEVICEMOCK_H__

#include "../../src/backend/IDevice.h"
#include "gmock/gmock.h"

class DeviceMock : public IDevice {
   public:
    MOCK_METHOD(void, connectWiFi, (), (override));
    MOCK_METHOD(bool, isWiFiConnected, (), (override));
    MOCK_METHOD(void, powerOff, (), (override));
    MOCK_METHOD(float, getBatteryLevelInPercent, (), (override));
    MOCK_METHOD(unsigned int, getBatteryWarningLevel, (), (override));
};

#endif  // __DEVICEMOCK_H__