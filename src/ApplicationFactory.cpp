#include "ApplicationFactory.h"

#include "backend/BlindsAccess.h"
#include "backend/BlindsManager.h"
#include "backend/DeviceAccess.h"
#include "backend/DeviceDataAccess.h"
#include "backend/DeviceManager.h"
#include "backend/HttpBlind.h"
#include "firmwareAbstraction/Device.h"
#include "firmwareAbstraction/DeviceData.h"
#include "firmwareAbstraction/HardwareButton.h"
#include "firmwareAbstraction/HttpClientWrapper.h"
#include "firmwareAbstraction/SelectionButton.h"
#include "firmwareAbstraction/StatusBar.h"
#include "firmwareAbstraction/TouchButton.h"

ApplicationFactory::~ApplicationFactory() {
    for (unsigned int configIndex = 0; configIndex < numberOfConfigs_;
         configIndex++) {
        delete *(selectionButtons_ + configIndex);
        delete *(blinds_ + configIndex);
        delete *(loopers_ + configIndex);
    }

    delete blindIds_;
    delete application_;
    delete blindsControlViewController_;
    delete blindsControlView_;
    delete powerOffButton_;
    delete toggleAllSelectionButton_;
    delete statusBar_;
    delete selectionButtons_;
    delete openButton_;
    delete closeButton_;
    delete tiltButton_;
    delete stopButton_;
    delete device_;
    delete deviceData_;
    delete httpClient_;
    delete blinds_;
    delete loopers_;
    delete deviceAccess_;
    delete deviceDataAccessPersistable_;
    delete deviceDataAccessEnablable_;
    delete blindsAccess_;
    delete blindsAccessLooper_;
    delete deviceManager_;
    delete blindsManagerBlind_;
    delete blindsManagerEnablable_;
    delete blindsManagerLooper_;
}

Application *ApplicationFactory::createApplication(
    ApplicationConfiguration *applicationConfiugration,
    BlindConfiguration *blindConfigurations, unsigned int numberOfConfigs) {
    applicationConfiguration_ = applicationConfiugration;
    blindConfigurations_ = blindConfigurations;
    numberOfConfigs_ = numberOfConfigs;
    blindIds_ = new unsigned int[numberOfConfigs_];
    for (unsigned int configIndex = 0; configIndex < numberOfConfigs_;
         configIndex++) {
        blindIds_[configIndex] = blindConfigurations_[configIndex].id;
    }

    createDevice();
    createDeviceData();
    createHttpClient();
    createBlinds();
    createDeviceAccess();
    createDeviceDataAccess();
    createBlindsAccess();
    createDeviceManager();
    createBlindsManager();
    createBlindsControlView();
    createBlindsControlViewController();
    application_ = new Application(blindsControlViewController_);
    return application_;
}

void ApplicationFactory::createDevice() {
    unsigned int connectionTimeoutInMilliseconds = 200;
    device_ = new Device(applicationConfiguration_->ssid,
                         applicationConfiguration_->passphrase,
                         connectionTimeoutInMilliseconds);
}

void ApplicationFactory::createDeviceData() {
    char storageName[50] = "M5Core2BlindsController";
    deviceData_ = new DeviceData(storageName);
}

void ApplicationFactory::createHttpClient() {
    httpClient_ = new HttpClientWrapper();
}

void ApplicationFactory::createBlinds() {
    blinds_ = new IBlind *[numberOfConfigs_];
    for (unsigned int configIndex = 0; configIndex < numberOfConfigs_;
         configIndex++) {
        HttpBlind *blind =
            new HttpBlind(*(blindConfigurations_ + configIndex), httpClient_,
                          applicationConfiguration_
                              ->timeoutBetweenHttpRequestsInMilliseconds);
        *(blinds_ + configIndex) = blind;

        *(loopers_ + configIndex) = blind;
    }
}

void ApplicationFactory::createDeviceAccess() {
    deviceAccess_ = new DeviceAccess(device_);
}

void ApplicationFactory::createDeviceDataAccess() {
    DeviceDataAccess *access = new DeviceDataAccess(deviceData_);
    deviceDataAccessPersistable_ = access;
    deviceDataAccessEnablable_ = access;
}

void ApplicationFactory::createBlindsAccess() {
    BlindsAccess *access =
        new BlindsAccess(blinds_, loopers_, numberOfConfigs_);
    blindsAccess_ = access;
    blindsAccessLooper_ = access;
}

void ApplicationFactory::createDeviceManager() {
    deviceManager_ =
        new DeviceManager(deviceAccess_, deviceDataAccessPersistable_);
}

void ApplicationFactory::createBlindsManager() {
    BlindsManager *blindsManager = new BlindsManager(
        blindIds_, numberOfConfigs_, deviceDataAccessEnablable_, blindsAccess_,
        blindsAccessLooper_);
    blindsManagerBlind_ = blindsManager;
    blindsManagerEnablable_ = blindsManager;
    blindsManagerLooper_ = blindsManager;
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

void ApplicationFactory::createBlindsControlViewController() {
    blindsControlViewController_ = new BlindsControlViewController(
        blindIds_, numberOfConfigs_, blindsControlView_, deviceManager_,
        blindsManagerEnablable_, blindsManagerBlind_, blindsManagerLooper_,
        applicationConfiguration_->idleTimeoutBeforeShutdownInMilliseconds);
}

ISelectionButton *ApplicationFactory::createSelectionButton(
    BlindConfiguration &blindconfiguration) {
    SelectionButton *button = new SelectionButton(
        blindconfiguration.buttonPositionX, blindconfiguration.buttonPositionY,
        blindconfiguration.buttonWidth, blindconfiguration.buttonHeight,
        blindconfiguration.id);
    return button;
}
