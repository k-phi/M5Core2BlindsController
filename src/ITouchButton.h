#ifndef __ITOUCHBUTTON_H__
#define __ITOUCHBUTTON_H__

class ITouchButton {
   public:
    virtual ~ITouchButton(){};
    virtual void load() = 0;
    virtual bool wasPressed() = 0;
    virtual void setLabel(const char* label) = 0;
};

#endif  // __ITOUCHBUTTON_H__