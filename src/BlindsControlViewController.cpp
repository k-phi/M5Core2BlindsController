#include "BlindsControlViewController.h"

#include <string.h>

#include <cmath>
#include <cstring>

BlindsControlViewController::BlindsControlViewController(
    unsigned int *blindIds, unsigned int numberOfIds, BlindsControlView *view,
    IDevice *device, IEnablable *enablable, IBlind *blind, ILooper *looper,
    long idleTimeoutInMilliseconds)
    : numberOfIds_(numberOfIds),
      view_(view),
      device_(device),
      enablable_(enablable),
      blind_(blind),
      looper_(looper),
      idleTimeoutInMilliseconds_(idleTimeoutInMilliseconds) {
    blindIds_ = new unsigned int[numberOfIds_];
    for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
        blindIds_[idIndex] = *(blindIds + idIndex);
    }
    areAllBlindsSelected_ = false;
    isWifiConnected_ = true;
    batteryLevelInPercent_ = 100.0f;
    batteryWarningLevel_ = 0;
    strcpy(statusMessage_, "OK");
    timeOfLastButtonPress_ = std::chrono::system_clock::now();
}

BlindsControlViewController::~BlindsControlViewController() {
    delete blindIds_;
}

void BlindsControlViewController::loadView() {
    view_->load();
    setSavedSelectionState();
    setInitialStatusValues();
}

void BlindsControlViewController::loop() {
    isAnyButtonPressed_ = false;

    loopPowerOffButton();
    loopSelectionButtons();
    loopToggleAllSelectionButtons();
    loopMoveCommandButtons();
    looper_->loop();
    loopStatusBar();

    bool isIdleTimeoutExceeded = isIdleTimoutExceeded();
    if (isIdleTimeoutExceeded) {
        device_->powerOff();
    }
}

void BlindsControlViewController::setSavedSelectionState() {
    for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
        unsigned int id = blindIds_[idIndex];
        ISelectionButton *button = view_->getBlindSelectionButton(id);
        bool isEnabled = enablable_->isEnabled(id);
        if (isEnabled) {
            button->select();
        } else {
            button->unselect();
        }
    }
}

void BlindsControlViewController::setInitialStatusValues() {
    IStatusBar *statusBar = view_->getStatusBar();
    statusBar->setWiFiConnectionStatus(isWifiConnected_);
    statusBar->setBatteryLevel(batteryLevelInPercent_);
    statusBar->setStatusMessage(statusMessage_);
}

void BlindsControlViewController::loopPowerOffButton() {
    if (view_->getPowerOffButton()->wasPressed()) {
        device_->powerOff();
        isAnyButtonPressed_ = true;
    }
}

void BlindsControlViewController::loopSelectionButtons() {
    for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
        unsigned int id = blindIds_[idIndex];
        ISelectionButton *button = view_->getBlindSelectionButton(id);
        if (button->wasPressed()) {
            bool isEnabled = enablable_->isEnabled(id);
            if (isEnabled) {
                enablable_->disable(id);
                button->unselect();
            } else {
                enablable_->enable(id);
                button->select();
            }
            isAnyButtonPressed_ = true;
        }
    }
}

void BlindsControlViewController::loopToggleAllSelectionButtons() {
    if (view_->getToggleAllSelectionButton()->wasPressed()) {
        areAllBlindsSelected_ = !areAllBlindsSelected_;
        for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
            unsigned int id = blindIds_[idIndex];
            ISelectionButton *button = view_->getBlindSelectionButton(id);
            if (areAllBlindsSelected_) {
                enablable_->enable(id);
                button->select();
            } else {
                enablable_->disable(id);
                button->unselect();
            }
        }
        isAnyButtonPressed_ = true;
    }
}

void BlindsControlViewController::loopMoveCommandButtons() {
    if (view_->getOpenButton()->wasPressed()) {
        blind_->open();
        isAnyButtonPressed_ = true;
    }

    if (view_->getCloseButton()->wasPressed()) {
        blind_->close();
        isAnyButtonPressed_ = true;
    }

    if (view_->getGoToTiltPositionButton()->wasPressed()) {
        blind_->tilt();
        isAnyButtonPressed_ = true;
    }

    if (view_->getStopButton()->wasPressed()) {
        blind_->stop();
        isAnyButtonPressed_ = true;
    }
}

void BlindsControlViewController::loopStatusBar() {
    IStatusBar *statusBar = view_->getStatusBar();
    char message[20] = "OK";

    bool isConnected = device_->isWiFiConnected();
    if (!isConnected) {
        strcpy(message, "Disconnected!");
    }
    if (isConnected != isWifiConnected_) {
        statusBar->setWiFiConnectionStatus(isConnected);
        isWifiConnected_ = isConnected;
    }

    float batteryLevel = device_->getBatteryLevelInPercent();
    if (batteryLevel < 10.0f) {
        strcpy(message, "Low battery!");
    }
    if (std::fabs(batteryLevel - batteryLevelInPercent_) > 0.5) {
        statusBar->setBatteryLevel(batteryLevel);
        batteryLevelInPercent_ = batteryLevel;
    }

    unsigned int warningLevel = device_->getBatteryWarningLevel();
    if (warningLevel != 0) {
        strcpy(message, "Battery error!");
    }
    if (warningLevel != batteryWarningLevel_) {
        batteryWarningLevel_ = warningLevel;
    }

    if (strcmp(statusMessage_, message) != 0) {
        statusBar->setStatusMessage(message);
        strcpy(statusMessage_, message);
    }
}

bool BlindsControlViewController::isIdleTimoutExceeded() {
    bool isExceeded = false;
    if (isAnyButtonPressed_) {
        timeOfLastButtonPress_ = std::chrono::system_clock::now();
    } else {
        long durationInMilliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now() - timeOfLastButtonPress_)
                .count();

        if (durationInMilliseconds > idleTimeoutInMilliseconds_) {
            isExceeded = true;
        }
    }

    return isExceeded;
}
