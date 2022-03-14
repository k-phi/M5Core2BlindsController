#ifndef __TOUCHBUTTONMOCK_H__
#define __TOUCHBUTTONMOCK_H__

#include "../../src/hmi/ITouchButton.h"
#include "gmock/gmock.h"

class TouchButtonMock : public ITouchButton {
   public:
    MOCK_METHOD(void, load, (), (override));
    MOCK_METHOD(void, setLabel, (const char* label), (override));
    MOCK_METHOD(bool, wasPressed, (), (override));
};

#endif  // __TOUCHBUTTONMOCK_H__