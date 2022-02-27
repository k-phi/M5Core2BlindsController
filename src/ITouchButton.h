#ifndef __ITOUCHBUTTON_H__
#define __ITOUCHBUTTON_H__

#include "UiControlBase.h"

class ITouchButton : public UiControlBase {
   public:
    virtual ~ITouchButton(){};
    ITouchButton(int x, int y, int width, int height, const char* label)
        : UiControlBase(x, y, width, height){};
    virtual void load() = 0;
    virtual bool wasPressed() = 0;
    virtual void setLabel(const char* label) = 0;
};

#endif  // __ITOUCHBUTTON_H__