#ifndef __STATUSBAR_H__
#define __STATUSBAR_H__

#include <M5Core2.h>

#include "../hmi/IStatusBar.h"

class StatusBar : public IStatusBar {
   public:
    StatusBar(int x, int y, int width, int height);
    ~StatusBar();
    virtual void load();
    virtual void setBatteryLevel(float batteryLevelInPercent);
    virtual void setStatusMessage(const char* message);
    virtual void setWiFiConnectionStatus(bool isConnected);

   private:
    int x_;
    int y_;
    int width_;
    int height_;
    Button* batteryStatus_;
    Button* statusMessage_;
    Button* wiFiStatus_;
};
#endif  // __STATUSBAR_H__