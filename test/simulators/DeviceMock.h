#ifndef __DEVICEMOCK_H__
#define __DEVICEMOCK_H__

#include "../../src/IDevice.h"
#include "gmock/gmock.h"

class DeviceMock : public IDevice {
   public:
    MOCK_METHOD(void, connectWiFi, (), (override));
    MOCK_METHOD(bool, isWiFiConnected, (), (override));
    MOCK_METHOD(void, powerOff, (), (override));
    MOCK_METHOD(float, getBatteryLevel, (), (override));
    MOCK_METHOD(uint8_t, getBatteryWarningLevel, (), (override));
};

#endif  // __DEVICEMOCK_H__