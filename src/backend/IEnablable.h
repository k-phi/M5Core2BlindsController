#ifndef __IENABLABLE_H__
#define __IENABLABLE_H__

class IEnablable {
   public:
    virtual ~IEnablable(){};
    virtual void enable(unsigned int id) = 0;
    virtual void disable(unsigned int id) = 0;
    virtual bool isEnabled(unsigned int id) = 0;
};

#endif  // __IENABLABLE_H__