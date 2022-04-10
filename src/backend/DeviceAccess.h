#ifndef __DEVICEACCESS_H__
#define __DEVICEACCESS_H__

#include "IDevice.h"

class DeviceAccess : public IDevice {
   public:
    DeviceAccess(IDevice *device);
    ~DeviceAccess();
    virtual void connectWiFi();
    virtual bool isWiFiConnected();
    virtual void powerOff();
    virtual float getBatteryLevelInPercent();
    virtual unsigned int getBatteryWarningLevel();

   private:
    IDevice *device_;
};
#endif  // __DEVICEACCESS_H__