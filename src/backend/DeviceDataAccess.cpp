/*
  DeviceDataAccess.cpp

  Copyright (c) 2022, Philipp Kraft.

  This file is part of M5Core2BlindsController. M5Core2BlindsController is free
  software: you can redistribute it and/or modify it under the terms of the GNU
  Lesser General Public License as published by the Free Software Foundation,
  either version 3 of the License, or (at your option) any later version.

  M5Core2BlindsController is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
  for more details.

  You should have received a copy of the GNU Lesser General Public License along
  with M5Core2BlindsController. If not, see <https://www.gnu.org/licenses/>.
*/

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
