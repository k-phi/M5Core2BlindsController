#ifndef __BLINDSMOCK_H__
#define __BLINDSMOCK_H__

#include "../../src/IBlinds.h"
#include "gmock/gmock.h"

class BlindsMock : public IBlinds {
   public:
    MOCK_METHOD(void, open, (unsigned int id), (override));
    MOCK_METHOD(void, close, (unsigned int id), (override));
    MOCK_METHOD(void, stop, (unsigned int id), (override));
    MOCK_METHOD(void, tilt, (unsigned int id), (override));
};

#endif  // __BLINDSMOCK_H__