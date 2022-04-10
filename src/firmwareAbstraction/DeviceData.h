#ifndef __DEVICEDATA_H__
#define __DEVICEDATA_H__

#include <Preferences.h>

#include "../backend/IDeviceData.h"

class DeviceData : public IDeviceData {
   public:
    DeviceData(char* storageName);
    ~DeviceData(){};
    virtual void saveBool(const char* key, bool value);
    virtual bool loadBool(const char* key);
    virtual bool clear();
    virtual void close();

   private:
    char* storageName_;
    Preferences preferences_;
};

#endif  // __DEVICEDATA_H__