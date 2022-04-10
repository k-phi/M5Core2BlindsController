#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/hmi/BlindsControlView.h"
#include "simulators/SelectionButtonMock.h"
#include "simulators/StatusBarMock.h"
#include "simulators/TouchButtonMock.h"

using ::testing::_;
using ::testing::Return;

TEST(BlindsControlViewTests, canCreateMockControls) {
    TouchButtonMock touchButton;
    StatusBarMock statusBar;
    SelectionButtonMock selectionButton;
    EXPECT_CALL(touchButton, load()).Times(1);
    EXPECT_CALL(statusBar, load()).Times(1);
    EXPECT_CALL(selectionButton, load()).Times(1);

    touchButton.load();
    statusBar.load();
    selectionButton.load();
}

TEST(BlindsControlViewTests, canCreateBlindsControlView) {
    TouchButtonMock goToTiltPositionButton;
    TouchButtonMock powerOffButton;
    TouchButtonMock toggleAllSelectionButton;
    StatusBarMock statusBar;
    SelectionButtonMock blindsSelectionButton;
    ISelectionButton *blindSelectionButtons[] = {&blindsSelectionButton};
    TouchButtonMock openButton;
    TouchButtonMock stopButton;
    TouchButtonMock closeButton;

    BlindsControlView blindsControlView(
        &goToTiltPositionButton, &powerOffButton, &toggleAllSelectionButton,
        &statusBar, blindSelectionButtons, 1, &openButton, &stopButton,
        &closeButton);
}

TEST(BlindsControlViewTests, load_callsLoadOnAllChildren) {
    TouchButtonMock goToTiltPositionButton;
    TouchButtonMock powerOffButton;
    TouchButtonMock toggleAllSelectionButton;
    StatusBarMock statusBar;
    SelectionButtonMock blindsSelectionButton0;
    SelectionButtonMock blindsSelectionButton1;
    ISelectionButton *blindSelectionButtons[] = {&blindsSelectionButton0,
                                                 &blindsSelectionButton1};
    TouchButtonMock openButton;
    TouchButtonMock stopButton;
    TouchButtonMock closeButton;

    EXPECT_CALL(goToTiltPositionButton, load()).Times(1);
    EXPECT_CALL(powerOffButton, load()).Times(1);
    EXPECT_CALL(toggleAllSelectionButton, load()).Times(1);
    EXPECT_CALL(statusBar, load()).Times(1);
    EXPECT_CALL(blindsSelectionButton0, load()).Times(1);
    EXPECT_CALL(blindsSelectionButton1, load()).Times(1);
    EXPECT_CALL(openButton, load()).Times(1);
    EXPECT_CALL(stopButton, load()).Times(1);
    EXPECT_CALL(closeButton, load()).Times(1);

    unsigned int numberOfSelectionButtons =
        sizeof(blindSelectionButtons) / sizeof(blindSelectionButtons[0]);
    EXPECT_EQ(2, numberOfSelectionButtons);

    BlindsControlView blindsControlView(
        &goToTiltPositionButton, &powerOffButton, &toggleAllSelectionButton,
        &statusBar, blindSelectionButtons, numberOfSelectionButtons,
        &openButton, &stopButton, &closeButton);

    blindsControlView.load();
}

TEST(BlindsControlViewTests,
     getBlindSelectionButton_returnsButtonWithMatchingId) {
    TouchButtonMock goToTiltPositionButton;
    TouchButtonMock powerOffButton;
    TouchButtonMock toggleAllSelectionButton;
    StatusBarMock statusBar;
    SelectionButtonMock blindsSelectionButton0;
    SelectionButtonMock blindsSelectionButton1;
    ISelectionButton *blindSelectionButtons[] = {&blindsSelectionButton0,
                                                 &blindsSelectionButton1};
    TouchButtonMock openButton;
    TouchButtonMock stopButton;
    TouchButtonMock closeButton;

    unsigned int buttonId0 = 42;
    EXPECT_CALL(blindsSelectionButton0, getId()).Times(3);
    ON_CALL(blindsSelectionButton0, getId()).WillByDefault(Return(buttonId0));
    unsigned int buttonId1 = 69;
    EXPECT_CALL(blindsSelectionButton1, getId()).Times(3);
    ON_CALL(blindsSelectionButton1, getId()).WillByDefault(Return(buttonId1));
    unsigned int numberOfSelectionButtons =
        sizeof(blindSelectionButtons) / sizeof(blindSelectionButtons[0]);
    EXPECT_EQ(2, numberOfSelectionButtons);

    BlindsControlView blindsControlView(
        &goToTiltPositionButton, &powerOffButton, &toggleAllSelectionButton,
        &statusBar, blindSelectionButtons, numberOfSelectionButtons,
        &openButton, &stopButton, &closeButton);

    ISelectionButton *matchingButton =
        blindsControlView.getBlindSelectionButton(buttonId1);
    EXPECT_EQ(buttonId1, matchingButton->getId());

    matchingButton = blindsControlView.getBlindSelectionButton(buttonId0);
    EXPECT_EQ(buttonId0, matchingButton->getId());
}

TEST(BlindsControlViewTests,
     getBlindSelectionButton_returnsNullIfNoButtonForIdPresent) {
             TouchButtonMock goToTiltPositionButton;
    TouchButtonMock powerOffButton;
    TouchButtonMock toggleAllSelectionButton;
    StatusBarMock statusBar;
    SelectionButtonMock blindsSelectionButton0;
    SelectionButtonMock blindsSelectionButton1;
    ISelectionButton *blindSelectionButtons[] = {&blindsSelectionButton0,
                                                 &blindsSelectionButton1};
    TouchButtonMock openButton;
    TouchButtonMock stopButton;
    TouchButtonMock closeButton;

    unsigned int buttonId0 = 42;
    EXPECT_CALL(blindsSelectionButton0, getId()).Times(1);
    ON_CALL(blindsSelectionButton0, getId()).WillByDefault(Return(buttonId0));
    unsigned int buttonId1 = 69;
    EXPECT_CALL(blindsSelectionButton1, getId()).Times(1);
    ON_CALL(blindsSelectionButton1, getId()).WillByDefault(Return(buttonId1));
    unsigned int numberOfSelectionButtons =
        sizeof(blindSelectionButtons) / sizeof(blindSelectionButtons[0]);
    EXPECT_EQ(2, numberOfSelectionButtons);

    BlindsControlView blindsControlView(
        &goToTiltPositionButton, &powerOffButton, &toggleAllSelectionButton,
        &statusBar, blindSelectionButtons, numberOfSelectionButtons,
        &openButton, &stopButton, &closeButton);

    ISelectionButton *matchingButton =
        blindsControlView.getBlindSelectionButton(666);
    EXPECT_EQ(nullptr, matchingButton);
}
