#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/DeviceAccess.h"
#include "simulators/DeviceMock.h"

using ::testing::Return;

TEST(DeviceAccessTest, canCreateDeviceAccess) {
    DeviceMock device;

    DeviceAccess access(&device);
}

TEST(DeviceAccessTest, connectWifi_callsDevice_connectWiFi) {
    DeviceMock device;
    EXPECT_CALL(device, connectWiFi()).Times(1);
    DeviceAccess access(&device);

    access.connectWiFi();
}

TEST(DeviceAccessTest, isWiFiConnected_callsDevice_isWiFiConnected) {
    DeviceMock device;
    EXPECT_CALL(device, isWiFiConnected()).Times(1);
    ON_CALL(device, isWiFiConnected()).WillByDefault(Return(true));
    DeviceAccess access(&device);

    EXPECT_EQ(true, access.isWiFiConnected());
}

TEST(DeviceAccessTest, powerOff_callsDevice_powerOff) {
    DeviceMock device;
    EXPECT_CALL(device, powerOff()).Times(1);
    DeviceAccess access(&device);

    access.powerOff();
}

TEST(DeviceAccessTest,
     getBatteryLevelInPercent_callsDevice_getBatteryLevelInPercent) {
    DeviceMock device;
    EXPECT_CALL(device, getBatteryLevelInPercent()).Times(1);
    float levelInPercent = 42.0f;
    ON_CALL(device, getBatteryLevelInPercent())
        .WillByDefault(Return(levelInPercent));
    DeviceAccess access(&device);

    EXPECT_FLOAT_EQ(levelInPercent, access.getBatteryLevelInPercent());
}

TEST(DeviceAccessTest,
     getBatteryWarningLevel_callsDevice_getBatteryWarningLevel) {
    DeviceMock device;
    EXPECT_CALL(device, getBatteryWarningLevel()).Times(1);
    unsigned int warningLevel = 42;
    ON_CALL(device, getBatteryWarningLevel())
        .WillByDefault(Return(warningLevel));
    DeviceAccess access(&device);

    EXPECT_EQ(warningLevel, access.getBatteryWarningLevel());
}
