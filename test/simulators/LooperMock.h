#ifndef __LOOPERMOCK_H__
#define __LOOPERMOCK_H__

#include "../../src/backend/ILooper.h"
#include "gmock/gmock.h"

class LooperMock : public ILooper {
   public:
    MOCK_METHOD(void, loop, (), (override));
};

#endif  // __LOOPERMOCK_H__