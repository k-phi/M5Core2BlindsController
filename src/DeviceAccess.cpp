#include "DeviceAccess.h"
DeviceAccess::DeviceAccess(IDevice *device) : device_(device) {}

DeviceAccess::~DeviceAccess() {}

void DeviceAccess::connectWiFi() { device_->connectWiFi(); }

bool DeviceAccess::isWiFiConnected() { return device_->isWiFiConnected(); }

void DeviceAccess::powerOff() { device_->powerOff(); }

float DeviceAccess::getBatteryLevelInPercent() {
    return device_->getBatteryLevelInPercent();
}

unsigned int DeviceAccess::getBatteryWarningLevel() {
    return device_->getBatteryWarningLevel();
}