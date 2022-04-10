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
    bool areAllBlindsSelected_;
    bool isAnyButtonPressed_;
    bool isWifiConnected_;
    float batteryLevelInPercent_;
    unsigned int batteryWarningLevel_;
    char statusMessage_[20];
    long idleTimeoutInMilliseconds_;
    std::chrono::time_point<std::chrono::system_clock> timeOfLastButtonPress_;
    BlindsControlView *view_;
    IDevice *device_;
    IEnablable *enablable_;
    IBlind *blind_;
    ILooper *looper_;
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