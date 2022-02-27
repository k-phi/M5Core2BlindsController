#include "TouchButton.h"

TouchButton::TouchButton(int x, int y, int width, int height, const char* label)
    : ITouchButton(x, y, width, height, label) {
    ButtonColors onColor = {BLACK, YELLOW, YELLOW};
    ButtonColors offColor = {YELLOW, BLACK, YELLOW};
    button_ = new Button(x, y, width, height, false, label, onColor, offColor,
                         TC_DATUM);
}

void TouchButton::load() { button_->draw(); }

bool TouchButton::wasPressed() { return button_->wasPressed(); }

void TouchButton::setLabel(const char* label)
{
    button_->setLabel(label);
}

TouchButton::~TouchButton() { delete button_; }
