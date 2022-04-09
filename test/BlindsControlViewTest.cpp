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
    ITouchButton *goToTiltPositionButton = new TouchButtonMock();
    ITouchButton *powerOffButton = new TouchButtonMock();
    ITouchButton *toggleAllSelectionButton = new TouchButtonMock();
    IStatusBar *statusBar = new StatusBarMock();
    ISelectionButton *blindsSelectionButton = new SelectionButtonMock();
    ISelectionButton *blindSelectionButtons[] = {blindsSelectionButton};
    ITouchButton *openButton = new TouchButtonMock();
    ITouchButton *stopButton = new TouchButtonMock();
    ITouchButton *closeButton = new TouchButtonMock();

    BlindsControlView *blindsControlView = new BlindsControlView(
        goToTiltPositionButton, powerOffButton, toggleAllSelectionButton,
        statusBar, blindSelectionButtons, 1, openButton, stopButton,
        closeButton);

    EXPECT_NE(blindsControlView, nullptr);
}

TEST(BlindsControlViewTests, load_callsLoadOnAllChildren) {
    TouchButtonMock goToTiltPositionButton;
    EXPECT_CALL(goToTiltPositionButton, load()).Times(1);
    TouchButtonMock powerOffButton;
    EXPECT_CALL(powerOffButton, load()).Times(1);
    TouchButtonMock toggleAllSelectionButton;
    EXPECT_CALL(toggleAllSelectionButton, load()).Times(1);
    StatusBarMock statusBar;
    EXPECT_CALL(statusBar, load()).Times(1);
    SelectionButtonMock blindsSelectionButton0;
    EXPECT_CALL(blindsSelectionButton0, load()).Times(1);
    SelectionButtonMock blindsSelectionButton1;
    EXPECT_CALL(blindsSelectionButton1, load()).Times(1);
    ISelectionButton *blindSelectionButtons[] = {&blindsSelectionButton0,
                                                 &blindsSelectionButton1};
    TouchButtonMock openButton;
    EXPECT_CALL(openButton, load()).Times(1);
    TouchButtonMock stopButton;
    EXPECT_CALL(stopButton, load()).Times(1);
    TouchButtonMock closeButton;
    EXPECT_CALL(closeButton, load()).Times(1);

    unsigned int numberOfSelectionButtons =
        sizeof(blindSelectionButtons) / sizeof(blindSelectionButtons[0]);
    EXPECT_EQ(2, numberOfSelectionButtons);

    BlindsControlView *blindsControlView = new BlindsControlView(
        &goToTiltPositionButton, &powerOffButton, &toggleAllSelectionButton,
        &statusBar, blindSelectionButtons, numberOfSelectionButtons,
        &openButton, &stopButton, &closeButton);

    blindsControlView->load();
}

TEST(BlindsControlViewTests,
     getBlindSelectionButton_returnsButtonWithMatchingId) {
    ITouchButton *goToTiltPositionButton = new TouchButtonMock();
    ITouchButton *powerOffButton = new TouchButtonMock();
    ITouchButton *toggleAllSelectionButton = new TouchButtonMock();
    IStatusBar *statusBar = new StatusBarMock();
    unsigned int buttonId0 = 42;
    SelectionButtonMock *blindsSelectionButton0 = new SelectionButtonMock();
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(3);
    ON_CALL(*blindsSelectionButton0, getId()).WillByDefault(Return(buttonId0));
    unsigned int buttonId1 = 69;
    SelectionButtonMock *blindsSelectionButton1 = new SelectionButtonMock();
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(3);
    ON_CALL(*blindsSelectionButton1, getId()).WillByDefault(Return(buttonId1));
    ISelectionButton *blindSelectionButtons[] = {blindsSelectionButton0,
                                                 blindsSelectionButton1};
    unsigned int numberOfSelectionButtons =
        sizeof(blindSelectionButtons) / sizeof(blindSelectionButtons[0]);
    EXPECT_EQ(2, numberOfSelectionButtons);
    ITouchButton *openButton = new TouchButtonMock();
    ITouchButton *stopButton = new TouchButtonMock();
    ITouchButton *closeButton = new TouchButtonMock();

    BlindsControlView *blindsControlView = new BlindsControlView(
        goToTiltPositionButton, powerOffButton, toggleAllSelectionButton,
        statusBar, blindSelectionButtons, numberOfSelectionButtons, openButton,
        stopButton, closeButton);

    ISelectionButton *matchingButton =
        blindsControlView->getBlindSelectionButton(buttonId1);
    EXPECT_EQ(buttonId1, matchingButton->getId());

    matchingButton = blindsControlView->getBlindSelectionButton(buttonId0);
    EXPECT_EQ(buttonId0, matchingButton->getId());

    delete blindsControlView;
}

TEST(BlindsControlViewTests,
     getBlindSelectionButton_returnsNullIfNoButtonForIdPresent) {
    ITouchButton *goToTiltPositionButton = new TouchButtonMock();
    ITouchButton *powerOffButton = new TouchButtonMock();
    ITouchButton *toggleAllSelectionButton = new TouchButtonMock();
    IStatusBar *statusBar = new StatusBarMock();
    unsigned int buttonId0 = 42;
    SelectionButtonMock *blindsSelectionButton0 = new SelectionButtonMock();
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(1);
    ON_CALL(*blindsSelectionButton0, getId()).WillByDefault(Return(buttonId0));
    unsigned int buttonId1 = 69;
    SelectionButtonMock *blindsSelectionButton1 = new SelectionButtonMock();
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(1);
    ON_CALL(*blindsSelectionButton1, getId()).WillByDefault(Return(buttonId1));
    ISelectionButton *blindSelectionButtons[] = {blindsSelectionButton0,
                                                 blindsSelectionButton1};
    unsigned int numberOfSelectionButtons =
        sizeof(blindSelectionButtons) / sizeof(blindSelectionButtons[0]);
    EXPECT_EQ(2, numberOfSelectionButtons);
    ITouchButton *openButton = new TouchButtonMock();
    ITouchButton *stopButton = new TouchButtonMock();
    ITouchButton *closeButton = new TouchButtonMock();

    BlindsControlView *blindsControlView = new BlindsControlView(
        goToTiltPositionButton, powerOffButton, toggleAllSelectionButton,
        statusBar, blindSelectionButtons, numberOfSelectionButtons, openButton,
        stopButton, closeButton);

    ISelectionButton *matchingButton =
        blindsControlView->getBlindSelectionButton(666);
    EXPECT_EQ(nullptr, matchingButton);

    delete blindsControlView;
}
