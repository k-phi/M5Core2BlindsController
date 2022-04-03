#ifndef __ENABLABLEMOCK_H__
#define __ENABLABLEMOCK_H__

#include "../../src/IEnablable.h"
#include "gmock/gmock.h"

class EnablableMock : public IEnablable {
   public:
    MOCK_METHOD(void, enable, (unsigned int id), (override));
    MOCK_METHOD(void, disable, (unsigned int id), (override));
    MOCK_METHOD(bool, isEnabled, (unsigned int id), (override));
};

#endif  // __ENABLABLEMOCK_H__