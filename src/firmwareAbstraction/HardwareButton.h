#ifndef __IHARDWAREBUTTON_H__
#define __IHARDWAREBUTTON_H__

#include <M5Core2.h>

#include "ITouchButton.h"

enum ButtonType { A, B, C };

class HardwareButton : public ITouchButton {
   public:
    virtual ~HardwareButton(){};
    HardwareButton(const char* label, ButtonType buttonType);
    virtual void load();
    virtual bool wasPressed();
    virtual void setLabel(const char* label);

   private:
    Button* button_;
};

#endif  // __IHARDWAREBUTTON_H__