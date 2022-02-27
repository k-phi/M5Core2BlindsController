#include "StatusBar.h"

#include <M5Core2.h>

StatusBar::StatusBar(int x, int y, int width, int height)
    : x_(x), y_(y), width_(width), height_(height) {
    cursorYOffset_ = 9;
}

void StatusBar::load() {
    M5.Lcd.drawRect(x_, y_, width_, height_, YELLOW);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(2);
}

void StatusBar::setBatteryLevel(float batteryLevelInPercent) {
    M5.Lcd.setCursor(5, cursorYOffset_);
    M5.Lcd.printf("%.0f%%", batteryLevelInPercent);
}

void StatusBar::setStatusMessage(const char* message) {
    M5.Lcd.setCursor(70, cursorYOffset_);
    M5.Lcd.print(message);
}

void StatusBar::setWiFiConnectionStatus(bool isConnected) {
    M5.Lcd.setCursor(230, cursorYOffset_);
    if (isConnected) {
        M5.Lcd.print("Online");
    } else {
        M5.Lcd.print("Offline");
    }
}
