#include "../src/BlindsControlView.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "simulators/SelectionButtonMock.h"
#include "simulators/StatusBarMock.h"
#include "simulators/TouchButtonMock.h"

using ::testing::_;
using ::testing::AtLeast;

TEST(BlindsControlViewTests, canCreateMockControls) {
    TouchButtonMock touchButton;
    StatusBarMock statusBar;
    SelectionButtonMock selectionButton;
    EXPECT_CALL(touchButton, load()).Times(AtLeast(1));
    EXPECT_CALL(statusBar, load()).Times(AtLeast(1));
    EXPECT_CALL(selectionButton, load()).Times(AtLeast(1));

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
    EXPECT_CALL(goToTiltPositionButton, load()).Times(AtLeast(1));
    TouchButtonMock powerOffButton;
    EXPECT_CALL(powerOffButton, load()).Times(AtLeast(1));
    TouchButtonMock toggleAllSelectionButton;
    EXPECT_CALL(toggleAllSelectionButton, load()).Times(AtLeast(1));
    StatusBarMock statusBar;
    EXPECT_CALL(statusBar, load()).Times(AtLeast(1));
    SelectionButtonMock blindsSelectionButton0;
    EXPECT_CALL(blindsSelectionButton0, load()).Times(AtLeast(1));
    SelectionButtonMock blindsSelectionButton1;
    EXPECT_CALL(blindsSelectionButton1, load()).Times(AtLeast(1));
    ISelectionButton *blindSelectionButtons[] = {&blindsSelectionButton0, &blindsSelectionButton1};
    TouchButtonMock openButton;
    EXPECT_CALL(openButton, load()).Times(AtLeast(1));
    TouchButtonMock stopButton;
    EXPECT_CALL(stopButton, load()).Times(AtLeast(1));    
    TouchButtonMock closeButton;
    EXPECT_CALL(closeButton, load()).Times(AtLeast(1));

    unsigned int numberOfSelectionButtons = sizeof(blindSelectionButtons)/sizeof(blindSelectionButtons[0]);
    EXPECT_EQ(2, numberOfSelectionButtons);

    BlindsControlView *blindsControlView = new BlindsControlView(
        &goToTiltPositionButton, &powerOffButton, &toggleAllSelectionButton,
        &statusBar, blindSelectionButtons, numberOfSelectionButtons, &openButton, &stopButton,
        &closeButton);

    blindsControlView->load();    
}
