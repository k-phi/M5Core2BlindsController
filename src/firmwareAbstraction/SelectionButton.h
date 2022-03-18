#ifndef __SELECTIONBUTTON_H__
#define __SELECTIONBUTTON_H__

#include <M5Core2.h>

#include "../hmi/ISelectionButton.h"

class SelectionButton : public ISelectionButton {
   public:
    virtual ~SelectionButton(){};
    SelectionButton(int x, int y, int width, int height);
    virtual void load();
    virtual bool wasPressed();
    virtual void select();
    virtual void unselect();
    virtual bool isSelected();

   private:
    Button* button_;
    bool isSelected_;
};

#endif  // __SELECTIONBUTTON_H__