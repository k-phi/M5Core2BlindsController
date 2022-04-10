#ifndef __BLINDSACCESS_H__
#define __BLINDSACCESS_H__

#include "IBlind.h"
#include "ILooper.h"
#include "IBlinds.h"

class BlindsAccess : public IBlinds, public ILooper {
   public:
    BlindsAccess(IBlind **blinds, ILooper **loopers,
                 unsigned int numberOfBlinds);
    virtual ~BlindsAccess();
    virtual void open(unsigned int id);
    virtual void close(unsigned int id);
    virtual void stop(unsigned int id);
    virtual void tilt(unsigned int id);
    virtual void loop();

   private:
    unsigned int numberOfBlinds_;
    IBlind **blinds_;
    ILooper **loopers_;
};
#endif  // __BLINDSACCESS_H__