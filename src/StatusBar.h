#ifndef __STATUSBAR_H__
#define __STATUSBAR_H__

#include "IStatusBar.h"

class StatusBar : public IStatusBar {
   public:
    StatusBar(int x, int y, int width, int height);
    virtual void load();
    virtual void setBatteryLevel(float batteryLevelInPercent);
    virtual void setStatusMessage(const char* message);
    virtual void setWiFiConnectionStatus(bool isConnected);

   private:
    int cursorYOffset_;
};
#endif  // __STATUSBAR_H__