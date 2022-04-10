#ifndef __DEVICEDATAMOCK_H__
#define __DEVICEDATAMOCK_H__

#include "../../src/backend/IDeviceData.h"
#include "gmock/gmock.h"

class DeviceDataMock : public IDeviceData {
   public:
    MOCK_METHOD(void, saveBool, (const char* key, bool value), (override));
    MOCK_METHOD(bool, loadBool, (const char* key), (override));
    MOCK_METHOD(bool, clear, (), (override));
    MOCK_METHOD(void, close, (), (override));
};

#endif  // __DEVICEDATAMOCK_H__