#ifndef __BLINDMOCK_H__
#define __BLINDMOCK_H__

#include "../../src/backend/IBlind.h"
#include "gmock/gmock.h"

class BlindMock : public IBlind {
   public:
    MOCK_METHOD(unsigned, getId, (), (override));
    MOCK_METHOD(void, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, tilt, (), (override));
};

#endif  // __BLINDMOCK_H__