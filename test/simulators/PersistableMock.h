#ifndef __PERSISTABLEMOCK_H__
#define __PERSISTABLEMOCK_H__

#include "../../src/backend/IPersistable.h"
#include "gmock/gmock.h"

class PersistableeMock : public IPersistable {
   public:
    MOCK_METHOD(void, save, (), (override));
};

#endif  // __PERSISTABLEMOCK_H__