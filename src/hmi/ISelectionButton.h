#ifndef __ISELECTIONBUTTON_H__
#define __ISELECTIONBUTTON_H__

class ISelectionButton {
   public:
    virtual ~ISelectionButton(){};
    virtual void load() = 0;
    virtual bool wasPressed() = 0;
    virtual void select() = 0;
    virtual void unselect() = 0;
    virtual bool isSelected() = 0;
    virtual unsigned int getId() = 0;
};

#endif  // __ISELECTIONBUTTON_H__