#ifndef __UICONTROLBASE_H__
#define __UICONTROLBASE_H__

class UiControlBase {
   public:
    UiControlBase(int x, int y, int width, int height)
        : x_(x), y_(y), width_(width), height_(height){};
    virtual void load() = 0;

   protected:
    int x_;
    int y_;
    int width_;
    int height_;
};
#endif  // __UICONTROLBASE_H__