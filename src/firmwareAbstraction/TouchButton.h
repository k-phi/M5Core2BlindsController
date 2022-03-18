#ifndef __TOUCHBUTTON_H__
#define __TOUCHBUTTON_H__

#include <M5Core2.h>

#include "../hmi/ITouchButton.h"

class TouchButton : public ITouchButton {
   public:
    virtual ~TouchButton();
    TouchButton(int x, int y, int width, int height, const char* label);
    virtual void load();
    virtual bool wasPressed();
    virtual void setLabel(const char* label);

   private:
    Button* button_;
};

#endif  // __TOUCHBUTTON_H__