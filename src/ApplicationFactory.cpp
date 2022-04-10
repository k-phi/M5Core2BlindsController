#include "ApplicationFactory.h"

#include "firmwareAbstraction/HardwareButton.h"
#include "firmwareAbstraction/SelectionButton.h"
#include "firmwareAbstraction/StatusBar.h"
#include "firmwareAbstraction/TouchButton.h"

ApplicationFactory::~ApplicationFactory()
{
    
}

Application *ApplicationFactory::createApplication(
    ApplicationConfiguration *applicationConfiugration,
    BlindConfiguration *blindConfigurations, unsigned int numberOfConfigs) {
    applicationConfiguration_ = applicationConfiugration;
    blindConfigurations_ = blindConfigurations;
    numberOfConfigs_ = numberOfConfigs;

    createBlindsControlView();
    return nullptr;
}

void ApplicationFactory::createBlindsControlView() {
    int screenWidth = 320;
    int buttonHeight = 30;

    powerOffButton_ = new TouchButton(106, 0, 106, buttonHeight, "Poff");
    toggleAllSelectionButton_ =
        new TouchButton(211, 0, 108, buttonHeight, "None");
    statusBar_ = new StatusBar(0, buttonHeight, screenWidth, buttonHeight);

    selectionButtons_ = new ISelectionButton *[numberOfConfigs_];
    for (unsigned int configIndex = 0; configIndex < numberOfConfigs_;
         configIndex++) {
        *(selectionButtons_ + configIndex) =
            createSelectionButton(*(blindConfigurations_ + configIndex));
    }

    openButton_ = new HardwareButton("Open", ButtonType::A);
    stopButton_ = new HardwareButton("Stop", ButtonType::B);
    closeButton_ = new HardwareButton("Close", ButtonType::C);
    tiltButton_ = new TouchButton(0, 0, 106, buttonHeight, "Tilt");

    blindsControlView_ = new BlindsControlView(
        tiltButton_, powerOffButton_, toggleAllSelectionButton_, statusBar_,
        selectionButtons_, numberOfConfigs_, openButton_, stopButton_,
        closeButton_);
}

ISelectionButton *ApplicationFactory::createSelectionButton(
    BlindConfiguration &blindconfiguration) {
    SelectionButton *button = new SelectionButton(
        blindconfiguration.buttonPositionX, blindconfiguration.buttonPositionY,
        blindconfiguration.buttonWidth, blindconfiguration.buttonHeight, blindconfiguration.id);
    return button;
}


