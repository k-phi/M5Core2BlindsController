#include "StatusBar.h"

StatusBar::StatusBar(int x, int y, int width, int height)
    : x_(x), y_(y), width_(width), height_(height) {
    ButtonColors onColor = {BLACK, YELLOW, BLACK};
    ButtonColors offColor = onColor;
    int batteryButtonWidth = 70;
    int statusMessageWidth = 160;

    batteryStatus_ = new Button(x + 1, y + 1, batteryButtonWidth, height - 2,
                                false, "", onColor, offColor, TL_DATUM);
    statusMessage_ =
        new Button(batteryButtonWidth + 2, y + 1, statusMessageWidth,
                   height - 2, false, "", onColor, offColor, TC_DATUM);
    wiFiStatus_ =
        new Button(batteryButtonWidth + statusMessageWidth + 2, y + 1,
                   width - batteryButtonWidth - statusMessageWidth - 3,
                   height - 2, false, "", onColor, offColor, TR_DATUM);
}

StatusBar::~StatusBar() {
    delete batteryStatus_;
    delete statusMessage_;
    delete wiFiStatus_;
}

void StatusBar::load() {
    M5.Lcd.drawRect(x_, y_, width_, height_, YELLOW);
    batteryStatus_->draw();
    statusMessage_->draw();
    wiFiStatus_->draw();
}

void StatusBar::setBatteryLevel(float batteryLevelInPercent) {
    char buffer[50];
    sprintf(buffer, "%.0f%%", batteryLevelInPercent);
    batteryStatus_->setLabel(buffer);
    batteryStatus_->draw();
}

void StatusBar::setStatusMessage(const char* message) {
    statusMessage_->setLabel(message);
    statusMessage_->draw();
}

void StatusBar::setWiFiConnectionStatus(bool isConnected) {
    if (isConnected) {
        wiFiStatus_->setLabel("Online");
    } else {
        wiFiStatus_->setLabel("Offline");
    }
    wiFiStatus_->draw();
}

