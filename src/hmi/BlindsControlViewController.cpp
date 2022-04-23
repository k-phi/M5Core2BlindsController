/*
  BlindsControlViewController.cpp

  Copyright (c) 2022, Philipp Kraft.

  This file is part of M5Core2BlindsController. M5Core2BlindsController is free
  software: you can redistribute it and/or modify it under the terms of the GNU
  Lesser General Public License as published by the Free Software Foundation,
  either version 3 of the License, or (at your option) any later version.

  M5Core2BlindsController is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
  for more details.

  You should have received a copy of the GNU Lesser General Public License along
  with M5Core2BlindsController. If not, see <https://www.gnu.org/licenses/>.
*/

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
    selectAllBlinds_ = true;
    isWifiConnected_ = true;
    batteryLevelInPercent_ = 100.0f;
    batteryWarningLevel_ = 0;
    strcpy(statusMessage_, "Loading...");
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
    ITouchButton *toggleAllButton = view_->getToggleAllSelectionButton();
    if (toggleAllButton->wasPressed()) {
        if (selectAllBlinds_) {
            toggleAllButton->setLabel("None");
        } else {
            toggleAllButton->setLabel("All");
        }

        for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
            unsigned int id = blindIds_[idIndex];
            ISelectionButton *button = view_->getBlindSelectionButton(id);
            if (selectAllBlinds_) {
                enablable_->enable(id);
                button->select();
            } else {
                enablable_->disable(id);
                button->unselect();
            }
        }
        selectAllBlinds_ = !selectAllBlinds_;
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
        device_->connectWiFi();
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
