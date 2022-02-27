#ifndef __ISTATUSBAR_H__
#define __ISTATUSBAR_H__

class IStatusBar {
   public:
    virtual ~IStatusBar(){};
    virtual void load() = 0;
    virtual void setBatteryLevel(float batteryLevelInPercent) = 0;
    virtual void setStatusMessage(const char* message) = 0;
    virtual void setWiFiConnectionStatus(bool isConnected) = 0;
};

#endif  // __ISTATUSBAR_H__