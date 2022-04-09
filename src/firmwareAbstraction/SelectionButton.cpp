#include "SelectionButton.h"

SelectionButton::SelectionButton(int x, int y, int width, int height,
                                 unsigned int id)
    : id_(id) {
    ButtonColors onColor = {BLACK, YELLOW, YELLOW};
    ButtonColors offColor = {YELLOW, BLACK, YELLOW};
    button_ = new Button(x, y, width, height, false, "", onColor, offColor);
    select();
}

void SelectionButton::load() { button_->draw(); }

bool SelectionButton::wasPressed() { return button_->wasPressed(); }

void SelectionButton::select() {
    button_->off = {YELLOW, NODRAW, YELLOW};
    button_->draw();
    isSelected_ = true;
}

void SelectionButton::unselect() {
    button_->off = {BLACK, NODRAW, YELLOW};
    button_->draw();
    isSelected_ = false;
}

bool SelectionButton::isSelected() { return isSelected_; }

unsigned int SelectionButton::getId() { return id_; }
