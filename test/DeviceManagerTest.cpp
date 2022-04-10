#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/backend/DeviceManager.h"
#include "simulators/DeviceMock.h"
#include "simulators/PersistableMock.h"

using ::testing::Return;

TEST(DeviceManagerTest, canCreateDeviceManager) {
    DeviceMock device;
    PersistableeMock persistable;

    DeviceManager access(&device, &persistable);
}

TEST(DeviceManagerTest, connectWifi_callsDevice_connectWiFi) {
    DeviceMock device;
    EXPECT_CALL(device, connectWiFi()).Times(1);
    PersistableeMock persistable;
    DeviceManager manager(&device, &persistable);

    manager.connectWiFi();
}

TEST(DeviceManagerTest, isWiFiConnected_callsDevice_isWiFiConnected) {
    DeviceMock device;
    EXPECT_CALL(device, isWiFiConnected()).Times(1);
    ON_CALL(device, isWiFiConnected()).WillByDefault(Return(true));
    PersistableeMock persistable;
    DeviceManager manager(&device, &persistable);

    EXPECT_EQ(true, manager.isWiFiConnected());
}

TEST(DeviceManagerTest,
     powerOff_callsPersistable_save_and_callsDevice_powerOff) {
    DeviceMock device;
    EXPECT_CALL(device, powerOff()).Times(1);
    PersistableeMock persistable;
    EXPECT_CALL(persistable, save()).Times(1);
    DeviceManager manager(&device, &persistable);

    manager.powerOff();
}

TEST(DeviceManagerTest,
     getBatteryLevelInPercent_callsDevice_getBatteryLevelInPercent) {
    DeviceMock device;
    EXPECT_CALL(device, getBatteryLevelInPercent()).Times(1);
    float levelInPercent = 42.0f;
    ON_CALL(device, getBatteryLevelInPercent())
        .WillByDefault(Return(levelInPercent));
    PersistableeMock persistable;
    DeviceManager manager(&device, &persistable);

    EXPECT_FLOAT_EQ(levelInPercent, manager.getBatteryLevelInPercent());
}

TEST(DeviceManagerTest,
     getBatteryWarningLevel_callsDevice_getBatteryWarningLevel) {
    DeviceMock device;
    EXPECT_CALL(device, getBatteryWarningLevel()).Times(1);
    unsigned int warningLevel = 42;
    ON_CALL(device, getBatteryWarningLevel())
        .WillByDefault(Return(warningLevel));
    PersistableeMock persistable;
    DeviceManager manager(&device, &persistable);

    EXPECT_EQ(warningLevel, manager.getBatteryWarningLevel());
}
