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