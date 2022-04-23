/*
  ApplicationFactory.h

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

#ifndef __APPLICATIONFACTORY_H__
#define __APPLICATIONFACTORY_H__

#include "Application.h"
#include "ApplicationConfiguration.h"
#include "BlindConfiguration.h"
#include "backend/IBlind.h"
#include "backend/IBlinds.h"
#include "backend/IDevice.h"
#include "backend/IDeviceData.h"
#include "backend/IEnablable.h"
#include "backend/IHttpClient.h"
#include "backend/ILooper.h"
#include "backend/IPersistable.h"
#include "hmi/BlindsControlView.h"
#include "hmi/BlindsControlViewController.h"
#include "hmi/ISelectionButton.h"
#include "hmi/IStatusBar.h"
#include "hmi/ITouchButton.h"

class ApplicationFactory {
   public:
    ~ApplicationFactory();
    Application *createApplication(
        ApplicationConfiguration *applicationConfiugration,
        BlindConfiguration *blindConfigurations, unsigned int numberOfConfigs);

   private:
    ApplicationConfiguration *applicationConfiguration_;
    BlindConfiguration *blindConfigurations_;
    unsigned int numberOfConfigs_;

    unsigned int *blindIds_;
    Application *application_;
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
    IDevice *device_;
    IDeviceData *deviceData_;
    IHttpClient *httpClient_;
    IBlind **blinds_;
    ILooper **loopers_;
    IDevice *deviceAccess_;
    IPersistable *deviceDataAccessPersistable_;
    IEnablable *deviceDataAccessEnablable_;
    IBlinds *blindsAccess_;
    ILooper *blindsAccessLooper_;
    IDevice *deviceManager_;
    IBlind *blindsManagerBlind_;
    IEnablable *blindsManagerEnablable_;
    ILooper *blindsManagerLooper_;

    void createDevice();
    void createDeviceData();
    void createHttpClient();
    void createBlinds();
    void createDeviceAccess();
    void createDeviceDataAccess();
    void createBlindsAccess();
    void createDeviceManager();
    void createBlindsManager();
    void createBlindsControlView();
    void createBlindsControlViewController();
    ISelectionButton *createSelectionButton(
        BlindConfiguration &blindconfiguration);
};

#endif  // __APPLICATIONFACTORY_H__