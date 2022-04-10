#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "hmi/BlindsControlViewController.h"

class Application {
   public:
    Application(BlindsControlViewController *controller);
    ~Application(){};
    void setup();
    void loop();

   private:
    BlindsControlViewController *controller_;
};

#endif  // __APPLICATION_H__