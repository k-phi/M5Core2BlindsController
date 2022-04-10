#include "BlindsControlView.h"

BlindsControlView::BlindsControlView(
    ITouchButton *goToTiltPositionButton, ITouchButton *powerOffButton,
    ITouchButton *toggleAllSelectionButton, IStatusBar *statusBar,
    ISelectionButton **blindSelectionButtons,
    unsigned int numberOfSelectionButtons, ITouchButton *openButton,
    ITouchButton *stopButton, ITouchButton *closeButton)
    : goToTiltPositionButton_(goToTiltPositionButton),
      powerOffButton_(powerOffButton),
      toggleAllSelectionButton_(toggleAllSelectionButton),
      statusBar_(statusBar),
      numberOfBlindSelectionButtons_(numberOfSelectionButtons),
      openButton_(openButton),
      stopButton_(stopButton),
      closeButton_(closeButton) {
    numberOfBlindSelectionButtons_ = numberOfSelectionButtons;
    blindSelectionButtons_ =
        new ISelectionButton *[numberOfBlindSelectionButtons_];
    for (unsigned int buttonIndex = 0;
         buttonIndex < numberOfBlindSelectionButtons_; buttonIndex++) {
        *(blindSelectionButtons_ + buttonIndex) =
            blindSelectionButtons[buttonIndex];
    }
}

BlindsControlView::~BlindsControlView() { delete blindSelectionButtons_; }

void BlindsControlView::load() {
    goToTiltPositionButton_->load();
    powerOffButton_->load();
    toggleAllSelectionButton_->load();
    statusBar_->load();

    for (unsigned int buttonIndex = 0;
         buttonIndex < numberOfBlindSelectionButtons_; buttonIndex++) {
        ISelectionButton *button = *(blindSelectionButtons_ + buttonIndex);
        if (button) {
            button->load();
        }
    }

    openButton_->load();
    stopButton_->load();
    closeButton_->load();
}

ITouchButton *BlindsControlView::getGoToTiltPositionButton() {
    return goToTiltPositionButton_;
}

ITouchButton *BlindsControlView::getPowerOffButton() { return powerOffButton_; }

ITouchButton *BlindsControlView::getToggleAllSelectionButton() {
    return toggleAllSelectionButton_;
}

IStatusBar *BlindsControlView::getStatusBar() { return statusBar_; }

ISelectionButton *BlindsControlView::getBlindSelectionButton(
    unsigned int buttonId) {
    ISelectionButton *matchingButton = nullptr;
    for (unsigned int buttonIndex = 0;
         buttonIndex < numberOfBlindSelectionButtons_; buttonIndex++) {
        ISelectionButton *button = *(blindSelectionButtons_ + buttonIndex);
        if (button && button->getId() == buttonId) {
            matchingButton = button;
        }
    }
    return matchingButton;
}

ITouchButton *BlindsControlView::getOpenButton() { return openButton_; }

ITouchButton *BlindsControlView::getStopButton() { return stopButton_; }

ITouchButton *BlindsControlView::getCloseButton() { return closeButton_; }
