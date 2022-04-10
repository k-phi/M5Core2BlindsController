#include "DeviceDataAccess.h"

#include <stdio.h>

DeviceDataAccess::DeviceDataAccess(IDeviceData *deviceData)
    : deviceData_(deviceData) {}

DeviceDataAccess::~DeviceDataAccess() { deviceData_->close(); }

void DeviceDataAccess::enable(unsigned int id) {
    blindEnabledCache_[id] = true;
}

void DeviceDataAccess::disable(unsigned int id) {
    blindEnabledCache_[id] = false;
}

bool DeviceDataAccess::isEnabled(unsigned int id) {
    size_t count = blindEnabledCache_.count(id);
    if (count == 0) {
        char key[10];
        convertIdToKey(id, key);
        bool isEnabled = deviceData_->loadBool(key);
        blindEnabledCache_[id] = isEnabled;
    }

    return blindEnabledCache_[id];
}

void DeviceDataAccess::save() {
    // TODO: Consider opening begin/end the storage access here if it's causing
    // problems staying open
    std::map<unsigned int, bool>::iterator it;
    for (it = blindEnabledCache_.begin(); it != blindEnabledCache_.end();
         it++) {
        unsigned int id = it->first;
        bool isEnabled = it->second;
        char key[10];
        convertIdToKey(id, key);
        bool storedValue = deviceData_->loadBool(key);
        if (isEnabled != storedValue) {
            deviceData_->saveBool(key, isEnabled);
        }
    }
}

void DeviceDataAccess::convertIdToKey(unsigned int id, char *key) {
    sprintf(key, "%d", id);
}
