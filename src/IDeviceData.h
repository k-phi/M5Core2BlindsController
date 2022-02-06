#ifndef __IDEVICEDATA_H__
#define __IDEVICEDATA_H__

class IDeviceData {
   public:
    virtual ~IDeviceData(){};
    virtual void saveBool(const char* key, bool value) = 0;
    virtual bool loadBool(const char* key) = 0;
    virtual bool clear() = 0;
    virtual void close() = 0;
};

#endif  // __IDEVICEDATA_H__