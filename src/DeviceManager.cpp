#include "DeviceManager.h"

DeviceManager::DeviceManager(IDevice *device, IPersistable *persistable)
    : device_(device), persistable_(persistable) {}

DeviceManager::~DeviceManager() {
    // TODO: Figure out while the BlindsAccessTest fail when deleting the
    // pointer  delete device_;  delete persistable_;
}

void DeviceManager::connectWiFi() { device_->connectWiFi(); }

bool DeviceManager::isWiFiConnected() { return device_->isWiFiConnected(); }

void DeviceManager::powerOff() {
    persistable_->save();
    device_->powerOff();
}

float DeviceManager::getBatteryLevelInPercent() {
    return device_->getBatteryLevelInPercent();
}

unsigned int DeviceManager::getBatteryWarningLevel() {
    return device_->getBatteryWarningLevel();
}
