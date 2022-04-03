#ifndef __DEVICEDATAACCESS_H__
#define __DEVICEDATAACCESS_H__

#include <map>

#include "BlindConfiguration.h"
#include "IDeviceData.h"
#include "IEnablable.h"
#include "IPersistable.h"

class DeviceDataAccess : public IPersistable, IEnablable {
   public:
    DeviceDataAccess(IDeviceData *deviceData);
    virtual ~DeviceDataAccess();
    virtual void enable(unsigned int id);
    virtual void disable(unsigned int id);
    virtual bool isEnabled(unsigned int id);
    virtual void save();

   private:
    IDeviceData *deviceData_;
    std::map<unsigned int, bool> blindEnabledCache_;
    void convertIdToKey(unsigned int id, char *key);
};
#endif  // __DEVICEDATAACCESS_H__