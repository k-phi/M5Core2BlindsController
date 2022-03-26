#ifndef __ILOOP_H__
#define __ILOOP_H__

class ILoop {
   public:
    virtual ~ILoop(){};
    virtual void loop() = 0;
};
#endif  // __ILOOP_H__