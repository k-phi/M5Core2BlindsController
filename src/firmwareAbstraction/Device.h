#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <WiFiMulti.h>

#include "../backend/IDevice.h"

class Device : public IDevice {
   public:
    Device(char *ssid, char *passphrase,
           const uint32_t &connection_timeout_in_milliseconds);
    ~Device(){};
    virtual void connectWiFi();
    virtual bool isWiFiConnected();
    virtual void powerOff();
    virtual float getBatteryLevelInPercent();
    virtual unsigned int getBatteryWarningLevel();

   private:
    char *ssid_;
    char *passphrase_;
    uint32_t connectionTimeoutInMilliseconds_;
    WiFiMulti wifiMulti_;
};
#endif  // __DEVICE_H__