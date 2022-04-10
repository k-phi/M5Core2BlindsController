#ifndef __APPLICATIONFACTORY_H__
#define __APPLICATIONFACTORY_H__

#include "ApplicationConfiguration.h"
#include "BlindConfiguration.h"
#include "Application.h"
#include "hmi/BlindsControlView.h"
#include "hmi/BlindsControlViewController.h"
#include "hmi/ISelectionButton.h"
#include "hmi/IStatusBar.h"
#include "hmi/ITouchButton.h"
#include "backend/BlindsAccess.h"
#include "backend/BlindsManager.h"
#include "backend/DeviceAccess.h"
#include "backend/DeviceDataAccess.h"
#include "backend/DeviceManager.h"
#include "backend/HttpBlind.h"
#include "backend/IDevice.h"
#include "backend/IDeviceData.h"
#include "backend/IHttpClient.h"


class ApplicationFactory {
   public:
    ~ApplicationFactory();
    Application* createApplication(
        ApplicationConfiguration* applicationConfiugration,
        BlindConfiguration* blindConfigurations, unsigned int numberOfConfigs);

   private:
   ApplicationConfiguration *applicationConfiguration_;
   unsigned int numberOfConfigs_;
   BlindConfiguration *blindConfigurations_;
   Application* application_;
   BlindsControlViewController *blindsControlViewController_;
   BlindsControlView *blindsControlView_;
   ITouchButton *powerOffButton_;
   ITouchButton *toggleAllSelectionButton_;
   IStatusBar *statusBar_;
   ISelectionButton **selectionButtons_;
   ITouchButton *openButton_;
   ITouchButton *closeButton_;
   ITouchButton *tiltButton_;
   ITouchButton *stopButton_;


    void createBlindsControlView();
    ISelectionButton* createSelectionButton(
        BlindConfiguration& blindconfiguration);
};

#endif  // __APPLICATIONFACTORY_H__