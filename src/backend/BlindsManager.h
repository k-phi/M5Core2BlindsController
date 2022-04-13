#ifndef __BLINDSMANAGER_H__
#define __BLINDSMANAGER_H__

#include "IBlind.h"
#include "IBlinds.h"
#include "IDevice.h"
#include "IEnablable.h"
#include "ILooper.h"

class BlindsManager : public IBlind, public IEnablable, public ILooper {
   public:
    BlindsManager(unsigned int *blindIds, unsigned int numberOfIds,
                  IEnablable *enablable, IBlinds *blinds, ILooper *looper);
    ~BlindsManager();
    virtual void open();
    virtual void close();
    virtual void stop();
    virtual void tilt();
    virtual void enable(unsigned int id);
    virtual void disable(unsigned int id);
    virtual bool isEnabled(unsigned int id);
    virtual void loop();
    virtual unsigned int getId();

   private:
    unsigned int *blindIds_;
    unsigned int numberOfIds_;
    IEnablable *enablable_;
    IBlinds *blinds_;
    ILooper *looper_;
};

#endif  // __BLINDSMANAGER_H__