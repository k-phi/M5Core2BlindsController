#ifndef __DEVICEMANAGER_H__
#define __DEVICEMANAGER_H__

#include "IDevice.h"
#include "IPersistable.h"

class DeviceManager : public IDevice {
   public:
    DeviceManager(IDevice *device, IPersistable *persistable);
    ~DeviceManager() {};
    virtual void connectWiFi();
    virtual bool isWiFiConnected();
    virtual void powerOff();
    virtual float getBatteryLevelInPercent();
    virtual unsigned int getBatteryWarningLevel();

   private:
    IDevice *device_;
    IPersistable *persistable_;
};

#endif  // __DEVICEMANAGER_H__