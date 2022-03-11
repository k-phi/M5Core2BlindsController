#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <WiFiMulti.h>

#include "IDevice.h"

class Device : public IDevice {
   public:
    Device(char *ssid, char *passphrase,
           const uint32_t &connection_timeout_in_milliseconds);
    ~Device(){};
    virtual void connectWiFi();
    virtual bool isWiFiConnected();
    virtual void powerOff();
    virtual float getBatteryLevel();
    virtual uint8_t getBatteryWarningLevel();

   private:
    char *ssid_;
    char *passphrase_;
    uint32_t connectionTimeoutInMilliseconds_;
    WiFiMulti wifiMulti_;
};
#endif  // __DEVICE_H__