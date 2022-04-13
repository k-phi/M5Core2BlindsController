#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "../src/hmi/BlindsControlView.h"
#include "../src/hmi/BlindsControlViewController.h"
#include "simulators/BlindMock.h"
#include "simulators/DeviceMock.h"
#include "simulators/EnablableMock.h"
#include "simulators/LooperMock.h"
#include "simulators/SelectionButtonMock.h"
#include "simulators/StatusBarMock.h"
#include "simulators/TouchButtonMock.h"

namespace {

using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;

class BlindsControlViewControllerTest : public ::testing::Test {
   protected:
    unsigned int blindIds[2] = {42, 69};
    unsigned int numberOfBlindIds;
    long idleTimeoutInMilliseconds = 20;
    TouchButtonMock *goToTiltPositionButton;
    TouchButtonMock *powerOffButton;
    TouchButtonMock *toggleAllSelectionButton;
    StatusBarMock *statusBar;
    SelectionButtonMock *blindsSelectionButton0;
    SelectionButtonMock *blindsSelectionButton1;
    TouchButtonMock *openButton;
    TouchButtonMock *stopButton;
    TouchButtonMock *closeButton;
    BlindsControlView *blindsControlView;
    DeviceMock *device;
    EnablableMock *enablable;
    BlindMock *blind;
    LooperMock *looper;
    BlindsControlViewController *controller;

    BlindsControlViewControllerTest() {}
    virtual ~BlindsControlViewControllerTest() {}

    virtual void SetUp() override { setupObjects(); }

    void setupObjects() {
        numberOfBlindIds = sizeof(blindIds) / sizeof(blindIds[0]);
        powerOffButton = new TouchButtonMock();
        toggleAllSelectionButton = new TouchButtonMock();
        statusBar = new StatusBarMock();
        blindsSelectionButton0 = new SelectionButtonMock();
        ON_CALL(*blindsSelectionButton0, getId())
            .WillByDefault(Return(blindIds[0]));
        blindsSelectionButton1 = new SelectionButtonMock();
        ON_CALL(*blindsSelectionButton1, getId())
            .WillByDefault(Return(blindIds[1]));
        ISelectionButton *blindSelectionButtons[] = {blindsSelectionButton0,
                                                     blindsSelectionButton1};
        unsigned int numberOfSelectionButtons =
            sizeof(blindSelectionButtons) / sizeof(blindSelectionButtons[0]);
        openButton = new TouchButtonMock();
        closeButton = new TouchButtonMock();
        goToTiltPositionButton = new TouchButtonMock();
        stopButton = new TouchButtonMock();
        blindsControlView = new BlindsControlView(
            goToTiltPositionButton, powerOffButton, toggleAllSelectionButton,
            statusBar, blindSelectionButtons, numberOfSelectionButtons,
            openButton, stopButton, closeButton);

        device = new DeviceMock();
        enablable = new EnablableMock();
        blind = new BlindMock();
        looper = new LooperMock();

        controller = new BlindsControlViewController(
            blindIds, numberOfBlindIds, blindsControlView, device, enablable,
            blind, looper, idleTimeoutInMilliseconds);
    }

    void setupCommonLoopExpectations(unsigned int numberOfIterations) {
        EXPECT_CALL(*powerOffButton, wasPressed()).Times(numberOfIterations);
        EXPECT_CALL(*blindsSelectionButton0, wasPressed())
            .Times(numberOfIterations);
        EXPECT_CALL(*blindsSelectionButton1, wasPressed())
            .Times(numberOfIterations);
        EXPECT_CALL(*toggleAllSelectionButton, wasPressed())
            .Times(numberOfIterations);
        EXPECT_CALL(*openButton, wasPressed()).Times(numberOfIterations);
        EXPECT_CALL(*closeButton, wasPressed()).Times(numberOfIterations);
        EXPECT_CALL(*goToTiltPositionButton, wasPressed())
            .Times(numberOfIterations);
        EXPECT_CALL(*stopButton, wasPressed()).Times(numberOfIterations);
        EXPECT_CALL(*looper, loop()).Times(numberOfIterations);
        EXPECT_CALL(*device, isWiFiConnected()).Times(numberOfIterations);
        EXPECT_CALL(*device, getBatteryLevelInPercent())
            .Times(numberOfIterations);
        EXPECT_CALL(*device, getBatteryWarningLevel())
            .Times(numberOfIterations);
    }

    virtual void TearDown() override {
        delete goToTiltPositionButton;
        delete powerOffButton;
        delete toggleAllSelectionButton;
        delete statusBar;
        delete blindsSelectionButton0;
        delete blindsSelectionButton1;
        delete openButton;
        delete stopButton;
        delete closeButton;
        delete blindsControlView;
        delete device;
        delete enablable;
        delete blind;
        delete looper;
        delete controller;
    }
};

TEST_F(BlindsControlViewControllerTest, canCreateControllerAndLoop) {
    EXPECT_NE(controller, nullptr);
}

TEST_F(BlindsControlViewControllerTest, loadView_loadsAllUiElements) {
    EXPECT_CALL(*goToTiltPositionButton, load()).Times(1);
    EXPECT_CALL(*powerOffButton, load()).Times(1);
    EXPECT_CALL(*toggleAllSelectionButton, load()).Times(1);
    EXPECT_CALL(*statusBar, load()).Times(1);
    EXPECT_CALL(*statusBar, setWiFiConnectionStatus(true)).Times(1);
    EXPECT_CALL(*statusBar, setBatteryLevel(100.0f)).Times(1);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("Loading..."))).Times(1);
    EXPECT_CALL(*blindsSelectionButton0, load()).Times(1);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton0, unselect()).Times(1);
    EXPECT_CALL(*blindsSelectionButton1, load()).Times(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton1, unselect()).Times(1);
    EXPECT_CALL(*openButton, load()).Times(1);
    EXPECT_CALL(*stopButton, load()).Times(1);
    EXPECT_CALL(*closeButton, load()).Times(1);
    EXPECT_CALL(*enablable, isEnabled(_)).Times(numberOfBlindIds);

    controller->loadView();
}

TEST_F(BlindsControlViewControllerTest, loop_callsPowerOffOnButtonPressed) {
    setupCommonLoopExpectations(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(2);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    ON_CALL(*powerOffButton, wasPressed()).WillByDefault(Return(true));
    EXPECT_CALL(*device, powerOff()).Times(1);

    controller->loop();
}

TEST_F(BlindsControlViewControllerTest, loop_disablesIfEnabledOnButtonPressed) {
    setupCommonLoopExpectations(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(2);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    ON_CALL(*blindsSelectionButton1, wasPressed()).WillByDefault(Return(true));
    ON_CALL(*enablable, isEnabled(blindIds[1])).WillByDefault(Return(true));
    EXPECT_CALL(*enablable, isEnabled(blindIds[1])).Times(1);
    EXPECT_CALL(*enablable, disable(blindIds[1])).Times(1);
    EXPECT_CALL(*blindsSelectionButton1, unselect()).Times(1);

    controller->loop();
}

TEST_F(BlindsControlViewControllerTest, loop_enablesIfDisabledOnButtonPressed) {
    setupCommonLoopExpectations(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(2);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    ON_CALL(*blindsSelectionButton1, wasPressed()).WillByDefault(Return(true));
    ON_CALL(*enablable, isEnabled(blindIds[1])).WillByDefault(Return(false));
    EXPECT_CALL(*enablable, isEnabled(blindIds[1])).Times(1);
    EXPECT_CALL(*enablable, enable(blindIds[1])).Times(1);
    EXPECT_CALL(*blindsSelectionButton1, select()).Times(1);

    controller->loop();
}

TEST_F(BlindsControlViewControllerTest,
       loop_enablesAllFirstTimeOnButtonPressed) {
    setupCommonLoopExpectations(1);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    ON_CALL(*toggleAllSelectionButton, wasPressed())
        .WillByDefault(Return(true));
    EXPECT_CALL(*enablable, enable(blindIds[0])).Times(1);
    EXPECT_CALL(*enablable, enable(blindIds[1])).Times(1);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(4);
    EXPECT_CALL(*blindsSelectionButton0, select()).Times(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(4);
    EXPECT_CALL(*blindsSelectionButton1, select()).Times(1);

    controller->loop();
}

TEST_F(BlindsControlViewControllerTest,
       loop_disablesAllSecondTimeOnButtonPressed) {
    setupCommonLoopExpectations(2);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    ON_CALL(*toggleAllSelectionButton, wasPressed())
        .WillByDefault(Return(true));
    EXPECT_CALL(*enablable, enable(blindIds[0])).Times(1);
    EXPECT_CALL(*enablable, enable(blindIds[1])).Times(1);
    EXPECT_CALL(*enablable, disable(blindIds[0])).Times(1);
    EXPECT_CALL(*enablable, disable(blindIds[1])).Times(1);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(8);
    EXPECT_CALL(*blindsSelectionButton0, select()).Times(1);
    EXPECT_CALL(*blindsSelectionButton0, unselect()).Times(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(8);
    EXPECT_CALL(*blindsSelectionButton1, select()).Times(1);
    EXPECT_CALL(*blindsSelectionButton1, unselect()).Times(1);

    controller->loop();
    controller->loop();
}

TEST_F(BlindsControlViewControllerTest, loop_callsOpenOnButtonPressed) {
    setupCommonLoopExpectations(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(2);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    ON_CALL(*openButton, wasPressed()).WillByDefault(Return(true));
    EXPECT_CALL(*blind, open()).Times(1);

    controller->loop();
}

TEST_F(BlindsControlViewControllerTest, loop_callsCloseOnButtonPressed) {
    setupCommonLoopExpectations(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(2);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    ON_CALL(*closeButton, wasPressed()).WillByDefault(Return(true));
    EXPECT_CALL(*blind, close()).Times(1);

    controller->loop();
}

TEST_F(BlindsControlViewControllerTest, loop_callsTiltOnButtonPressed) {
    setupCommonLoopExpectations(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(2);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    ON_CALL(*goToTiltPositionButton, wasPressed()).WillByDefault(Return(true));
    EXPECT_CALL(*blind, tilt()).Times(1);

    controller->loop();
}

TEST_F(BlindsControlViewControllerTest, loop_callsStopOnButtonPressed) {
    setupCommonLoopExpectations(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(2);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    ON_CALL(*stopButton, wasPressed()).WillByDefault(Return(true));
    EXPECT_CALL(*blind, stop()).Times(1);

    controller->loop();
}

TEST_F(BlindsControlViewControllerTest,
       loop_setsOkValuesIfDifferentFromDefaultsInStatusBar) {
    setupCommonLoopExpectations(1);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(2);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(2);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));

    bool isConnected = true;
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(isConnected));
    float batteryLevelInPercent = 99.4f;
    ON_CALL(*device, getBatteryLevelInPercent())
        .WillByDefault(Return(batteryLevelInPercent));
    EXPECT_CALL(*statusBar, setBatteryLevel(batteryLevelInPercent)).Times(1);
    unsigned int warningLevel = 0;
    ON_CALL(*device, getBatteryWarningLevel())
        .WillByDefault(Return(warningLevel));

    controller->loop();
}

TEST_F(BlindsControlViewControllerTest, loop_setsDisconnectedInStatusBarOnce) {
    setupCommonLoopExpectations(2);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(4);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(4);

    bool isConnected = false;
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(isConnected));
    EXPECT_CALL(*statusBar, setWiFiConnectionStatus(isConnected)).Times(1);
    float batteryLevelInPercent = 99.4f;
    ON_CALL(*device, getBatteryLevelInPercent())
        .WillByDefault(Return(batteryLevelInPercent));
    EXPECT_CALL(*statusBar, setBatteryLevel(batteryLevelInPercent)).Times(1);
    unsigned int warningLevel = 0;
    ON_CALL(*device, getBatteryWarningLevel())
        .WillByDefault(Return(warningLevel));
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("Disconnected!"))).Times(1);

    controller->loop();
    controller->loop();
}

TEST_F(BlindsControlViewControllerTest, loop_setsLowBatteryInStatusBarOnce) {
    setupCommonLoopExpectations(2);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(4);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(4);

    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    float batteryLevelInPercent = 9.2f;
    ON_CALL(*device, getBatteryLevelInPercent())
        .WillByDefault(Return(batteryLevelInPercent));
    EXPECT_CALL(*statusBar, setBatteryLevel(batteryLevelInPercent)).Times(1);
    unsigned int warningLevel = 0;
    ON_CALL(*device, getBatteryWarningLevel())
        .WillByDefault(Return(warningLevel));
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("Low battery!"))).Times(1);

    controller->loop();
    controller->loop();
}

TEST_F(BlindsControlViewControllerTest, loop_setsBatteryErrorInStatusBarOnce) {
    setupCommonLoopExpectations(2);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(4);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(4);

    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    float batteryLevelInPercent = 99.2f;
    ON_CALL(*device, getBatteryLevelInPercent())
        .WillByDefault(Return(batteryLevelInPercent));
    EXPECT_CALL(*statusBar, setBatteryLevel(batteryLevelInPercent)).Times(1);
    unsigned int warningLevel = 2;
    ON_CALL(*device, getBatteryWarningLevel())
        .WillByDefault(Return(warningLevel));
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("Battery error!"))).Times(1);

    controller->loop();
    controller->loop();
}

TEST_F(BlindsControlViewControllerTest,
       loop_powersOffAfterIdleTimoutIsExceeded) {
    setupCommonLoopExpectations(2);
    EXPECT_CALL(*blindsSelectionButton1, getId()).Times(4);
    EXPECT_CALL(*blindsSelectionButton0, getId()).Times(4);
    EXPECT_CALL(*statusBar, setStatusMessage(StrEq("OK"))).Times(1);
    ON_CALL(*device, isWiFiConnected()).WillByDefault(Return(true));
    ON_CALL(*device, getBatteryLevelInPercent()).WillByDefault(Return(99.5));
    EXPECT_CALL(*device, powerOff()).Times(1);

    controller->loop();
    std::this_thread::sleep_for(
        std::chrono::milliseconds(idleTimeoutInMilliseconds + 2));
    controller->loop();
}

}  // namespace
