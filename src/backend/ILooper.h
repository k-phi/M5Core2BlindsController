#ifndef __ILOOPER_H__
#define __ILOOPER_H__

class ILooper {
   public:
    virtual ~ILooper(){};
    virtual void loop() = 0;
};

#endif  // __ILOOPER_H__