/*
  BlindsControlViewController.h

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

#ifndef __BLINDSCONTROLVIEWCONTROLLER_H__
#define __BLINDSCONTROLVIEWCONTROLLER_H__

#ifdef _M5Core2_H_
#undef min  // Avoid Arduino compiler issue with redefinition of min in chrono
#endif

#include <chrono>

#include "../backend/IBlind.h"
#include "../backend/IDevice.h"
#include "../backend/IEnablable.h"
#include "../backend/ILooper.h"
#include "BlindsControlView.h"

class BlindsControlViewController : public ILooper {
   public:
    BlindsControlViewController(unsigned int *blindIds,
                                unsigned int numberOfIds,
                                BlindsControlView *view, IDevice *device,
                                IEnablable *enablable, IBlind *blind,
                                ILooper *looper,
                                long idleTimeoutInMilliseconds);
    ~BlindsControlViewController();
    void loadView();
    void loop();

   private:
    unsigned int *blindIds_;
    unsigned int numberOfIds_;
    BlindsControlView *view_;
    IDevice *device_;
    IEnablable *enablable_;
    IBlind *blind_;
    ILooper *looper_;
    long idleTimeoutInMilliseconds_;
    bool selectAllBlinds_;
    bool isAnyButtonPressed_;
    bool isWifiConnected_;
    float batteryLevelInPercent_;
    unsigned int batteryWarningLevel_;
    char statusMessage_[20];
    std::chrono::time_point<std::chrono::system_clock> timeOfLastButtonPress_;
    void setSavedSelectionState();
    void setInitialStatusValues();
    void loopPowerOffButton();
    void loopSelectionButtons();
    void loopToggleAllSelectionButtons();
    void loopMoveCommandButtons();
    void loopStatusBar();
    bool isIdleTimoutExceeded();
};

#endif  // __BLINDSCONTROLVIEWCONTROLLER_H__