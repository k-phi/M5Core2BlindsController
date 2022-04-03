#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/DeviceDataAccess.h"
#include "simulators/DeviceDataMock.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;

TEST(DeviceDataAccessTest, canCreateDeviceDataAccess) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, close()).Times(1);

    DeviceDataAccess access(&deviceData);
}

TEST(DeviceDataAccessTest, enable_doesNotCallDeviceData) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, saveBool(_, _)).Times(0);
    EXPECT_CALL(deviceData, close()).Times(1);
    DeviceDataAccess access(&deviceData);

    access.enable(42);
}

TEST(DeviceDataAccessTest, disable_doesNotCallDeviceData) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, saveBool(_, _)).Times(0);
    EXPECT_CALL(deviceData, close()).Times(1);
    DeviceDataAccess access(&deviceData);

    access.disable(42);
}

TEST(DeviceDataAccessTest, isEnabled_loadsStateFromDeviceDataIfNotInCache) {
    DeviceDataMock deviceData;
    ON_CALL(deviceData, loadBool(_)).WillByDefault(Return(true));
    EXPECT_CALL(deviceData, loadBool(StrEq("42"))).Times(1);
    EXPECT_CALL(deviceData, close()).Times(1);
    DeviceDataAccess access(&deviceData);

    access.isEnabled(42);
}

TEST(DeviceDataAccessTest, isEnabled_loadsStateFromDeviceDataOnlyOnce) {
    DeviceDataMock deviceData;
    ON_CALL(deviceData, loadBool(_)).WillByDefault(Return(true));
    EXPECT_CALL(deviceData, loadBool(StrEq("42"))).Times(1);
    EXPECT_CALL(deviceData, close()).Times(1);
    DeviceDataAccess access(&deviceData);

    unsigned int deviceId = 42;
    access.isEnabled(deviceId);
    access.isEnabled(deviceId);
}

TEST(DeviceDataAccessTest, isEnabled_returnsCachedState) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, loadBool(_)).Times(0);
    EXPECT_CALL(deviceData, close()).Times(1);
    DeviceDataAccess access(&deviceData);

    unsigned int firstDeviceId = 42;
    access.disable(firstDeviceId);
    EXPECT_EQ(false, access.isEnabled(firstDeviceId));

    unsigned int secondDeviceId = 69;
    access.enable(secondDeviceId);
    EXPECT_EQ(true, access.isEnabled(secondDeviceId));
}

TEST(DeviceDataAccessTest, save_doesNotCallDeviceDataIfCachIsEmpty) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, saveBool(_, _)).Times(0);
    EXPECT_CALL(deviceData, close()).Times(1);
    DeviceDataAccess access(&deviceData);

    access.save();
}

TEST(DeviceDataAccessTest, save_savesCachedStatesToDeviceData) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, saveBool(StrEq("69"), false)).Times(1);
    EXPECT_CALL(deviceData, saveBool(StrEq("42"), true)).Times(1);
    EXPECT_CALL(deviceData, close()).Times(1);
    DeviceDataAccess access(&deviceData);

    access.enable(42);
    access.disable(69);
    access.save();
}