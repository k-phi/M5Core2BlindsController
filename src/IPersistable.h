#ifndef __IPERSISTABLE_H__
#define __IPERSISTABLE_H__

class IPersistable {
   public:
    virtual ~IPersistable(){};
    virtual void save() = 0;
    virtual void load() = 0;
};

#endif  // __IPERSISTABLE_H__