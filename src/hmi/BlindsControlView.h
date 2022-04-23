/*
  BlindsControlView.h

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

#ifndef __BLINDSCONTROLVIEW_H__
#define __BLINDSCONTROLVIEW_H__

#include "ISelectionButton.h"
#include "IStatusBar.h"
#include "ITouchButton.h"

class BlindsControlView {
   public:
    BlindsControlView(ITouchButton *goToTiltPositionButton,
                      ITouchButton *powerOffButton,
                      ITouchButton *toggleAllSelectionButton,
                      IStatusBar *statusBar,
                      ISelectionButton **blindSelectionButtons,
                      unsigned int numberOfSelectionButtons,
                      ITouchButton *openButton, ITouchButton *stopButton,
                      ITouchButton *closeButton);
    ~BlindsControlView();
    void load();
    ITouchButton *getGoToTiltPositionButton();
    ITouchButton *getPowerOffButton();
    ITouchButton *getToggleAllSelectionButton();
    IStatusBar *getStatusBar();
    ISelectionButton *getBlindSelectionButton(unsigned int buttonId);
    ITouchButton *getOpenButton();
    ITouchButton *getStopButton();
    ITouchButton *getCloseButton();

   private:
    ITouchButton *goToTiltPositionButton_;
    ITouchButton *powerOffButton_;
    ITouchButton *toggleAllSelectionButton_;
    IStatusBar *statusBar_;
    ISelectionButton **blindSelectionButtons_;
    unsigned int numberOfBlindSelectionButtons_;
    ITouchButton *openButton_;
    ITouchButton *stopButton_;
    ITouchButton *closeButton_;
};

#endif  // __BLINDSCONTROLVIEW_H__