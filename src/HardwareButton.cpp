#include "HardwareButton.h"
HardwareButton::HardwareButton(const char* label, ButtonType buttonType) {
    switch (buttonType) {
        case A:
            button_ = &M5.BtnA;
            break;
        case B:
            button_ = &M5.BtnB;
            break;
        case C:
            button_ = &M5.BtnC;
            break;
        default:
            Serial.printf(
                "Illegal button type [%d] selected. Initialization of hardware "
                "button failed.\n");
            break;
    }

    ButtonColors onColor = {BLACK, YELLOW, NODRAW};
    ButtonColors offColor = {BLACK, YELLOW, NODRAW};
    button_->on = onColor;
    button_->off = offColor;
    setLabel(label);
}

void HardwareButton::load() { button_->draw(); }

bool HardwareButton::wasPressed() { return button_->wasPressed(); }

void HardwareButton::setLabel(const char* label) { button_->setLabel(label); }
