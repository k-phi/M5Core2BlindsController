#ifndef __APPLICATIONFACTORY_H__
#define __APPLICATIONFACTORY_H__

#include "BlindConfiguration.h"
#include "hmi/BlindsControlView.h"
#include "hmi/ISelectionButton.h"

class ApplicationFactory {
   public:
    BlindsControlView* createBlindsControlView(
        BlindConfiguration* blindConfigurations, unsigned int numberOfConfigs);

   private:
    ISelectionButton* createSelectionButton(
        BlindConfiguration& blindconfiguration);
};
#endif  // __APPLICATIONFACTORY_H__