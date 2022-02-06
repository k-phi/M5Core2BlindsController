#ifndef __IDEVICE_H__
#define __IDEVICE_H__

class IDevice {
   public:
    virtual ~IDevice(){};
    virtual void connectWiFi() = 0;
    virtual bool isWiFiConnected() = 0;
    virtual void powerOff() = 0;
    virtual float getBatteryLevel() = 0;
    virtual uint8_t getBatteryWarningLevel() = 0;
};

#endif  // __IDEVICE_H__