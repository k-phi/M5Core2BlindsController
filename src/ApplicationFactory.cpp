#include "ApplicationFactory.h"

#include "hmi/ISelectionButton.h"
#include "firmwareAbstraction/HardwareButton.h"
#include "firmwareAbstraction/SelectionButton.h"
#include "firmwareAbstraction/StatusBar.h"
#include "firmwareAbstraction/TouchButton.h"

BlindsControlView *ApplicationFactory::createBlindsControlView(
    BlindConfiguration *blindConfigurations, unsigned int numberOfConfigs) {
    int screenWidth = 320;
    int buttonHeight = 30;
    TouchButton *goToTiltPositionButton =
        new TouchButton(0, 0, 106, buttonHeight, "Tilt");
    TouchButton *powerOffButton =
        new TouchButton(106, 0, 106, buttonHeight, "Poff");
    TouchButton *toggleAllSelectionButton =
        new TouchButton(211, 0, 108, buttonHeight, "None");
    StatusBar *statusBar =
        new StatusBar(0, buttonHeight, screenWidth, buttonHeight);

    ISelectionButton *selectionButtons[numberOfConfigs];
    for (unsigned int configIndex = 0; configIndex < numberOfConfigs;
         configIndex++) {
        *(selectionButtons + configIndex) =
            createSelectionButton(*(blindConfigurations + configIndex));
    }

    HardwareButton *openButton = new HardwareButton("Open", ButtonType::A);
    HardwareButton *stopButton = new HardwareButton("Stop", ButtonType::B);
    HardwareButton *closeButton = new HardwareButton("Close", ButtonType::C);

    BlindsControlView *view = new BlindsControlView(
        goToTiltPositionButton, powerOffButton, toggleAllSelectionButton, statusBar,
        selectionButtons, numberOfConfigs, openButton, stopButton, closeButton);
    return view;
}

ISelectionButton *ApplicationFactory::createSelectionButton(
    BlindConfiguration &blindconfiguration) {
    SelectionButton *button = new SelectionButton(
        blindconfiguration.buttonPositionX, blindconfiguration.buttonPositionY,
        blindconfiguration.buttonWidth, blindconfiguration.buttonHeight);
    return button;
}
