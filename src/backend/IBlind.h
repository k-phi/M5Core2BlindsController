#ifndef __IBLIND_H__
#define __IBLIND_H__

class IBlind {
   public:
    virtual ~IBlind(){};
    virtual unsigned int getId() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void stop() = 0;
    virtual void tilt() = 0;
};
#endif  // __IBLIND_H__