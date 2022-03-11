#include "Device.h"
#include <M5Core2.h>

Device::Device(char *ssid, char *passphrase,
               const uint32_t& connectionTimeoutInMilliseconds)
    : ssid_(ssid),
      passphrase_(passphrase),
      connectionTimeoutInMilliseconds_(connectionTimeoutInMilliseconds) {
    M5.begin(true, false, true, false);

    Serial.begin(115200);
    Serial.flush();

    wifiMulti_.addAP(ssid_, passphrase_);
    connectWiFi();
}

void Device::connectWiFi() {
    wifiMulti_.run(connectionTimeoutInMilliseconds_);
}

bool Device::isWiFiConnected() {
    bool isConnected = WiFi.status() == WL_CONNECTED;
    return isConnected;
}

void Device::powerOff() {
    M5.shutdown();
}

float Device::getBatteryLevel() {
    float batteryLevel = M5.Axp.GetBatteryLevel();
    return batteryLevel;
}

uint8_t Device::getBatteryWarningLevel() {
    uint8_t warningLevel = M5.Axp.GetWarningLevel();
    return warningLevel;
}
