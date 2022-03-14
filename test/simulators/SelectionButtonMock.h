#ifndef __SELECTIONBUTTONMOCK_H__
#define __SELECTIONBUTTONMOCK_H__

#include "../../src/hmi/ISelectionButton.h"
#include "gmock/gmock.h"

class SelectionButtonMock : public ISelectionButton {
   public:
    MOCK_METHOD(void, load, (), (override));
    MOCK_METHOD(bool, wasPressed, (), (override));
    MOCK_METHOD(void, select, (), (override));
    MOCK_METHOD(void, unselect, (), (override));
    MOCK_METHOD(bool, isSelected, (), (override));
};

#endif  // __SELECTIONBUTTONMOCK_H__