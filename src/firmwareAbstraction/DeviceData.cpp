#include "DeviceData.h"
#include <M5Core2.h>


DeviceData::DeviceData(char* storageName) : storageName_(storageName)
{
    Serial.println("Opening storage...");
    bool isSuccessful = preferences_.begin(storageName_);
    if (isSuccessful) {
        Serial.println("Storage opened successfully.");
    } else {
        Serial.println("Opening storage failed.");
    }
}

void DeviceData::saveBool(const char* key, bool value) 
{
    preferences_.putBool(key, value);
}

bool DeviceData::loadBool(const char* key) 
{
    bool value = preferences_.getBool(key);
    return value;
}

bool DeviceData::clear() 
{
    bool isCleared = preferences_.clear();
    return isCleared;
}

void DeviceData::close() 
{
    preferences_.end();
}
