#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/DeviceDataAccess.h"
#include "simulators/DeviceDataMock.h"

using ::testing::_;
using  ::testing::Return;
using ::testing::StrEq;

TEST(DeviceDataAccessTest, canCreateDeviceDataAccess) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, close()).Times(1);

    DeviceDataAccess access(&deviceData);
}

TEST(DeviceDataAccessTest, enable_doesNotCallDeviceData) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, saveBool(_,_)).Times(0);
    EXPECT_CALL(deviceData, close()).Times(1);
    DeviceDataAccess access(&deviceData);

    access.enable(42);
}

TEST(DeviceDataAccessTest, disable_doesNotCallDeviceData) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, saveBool(_,_)).Times(0);
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
    EXPECT_CALL(deviceData, saveBool(_,_)).Times(0);
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

// TEST(BlindsAccessTest, open_callsOpenOnCorrectBlind) {
//     BlindMock blind0;
//     unsigned int id0 = 5;
//     ON_CALL(blind0, getId()).WillByDefault(Return(id0));
//     EXPECT_CALL(blind0, getId()).Times(1);
//     EXPECT_CALL(blind0, open()).Times(0);
//     BlindMock blind1;
//     unsigned int id1 = 6;
//     ON_CALL(blind1, getId()).WillByDefault(Return(id1));
//     EXPECT_CALL(blind1, getId()).Times(1);
//     EXPECT_CALL(blind1, open()).Times(1);
//     LooperMock looper0;
//     LooperMock looper1;
//     IBlind *blinds[] = {&blind0, &blind1};
//     ILooper *loopers[] = {&looper0, &looper1};
//     unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
//     BlindsAccess access(blinds, loopers, numberOfBlinds);

//     access.open(id1);
// }

// TEST(BlindsAccessTest, open_doesNotCallOpenOnAnyBlindIfIdIsInvalid) {
//     BlindMock blind0;
//     unsigned int id0 = 5;
//     ON_CALL(blind0, getId()).WillByDefault(Return(id0));
//     EXPECT_CALL(blind0, getId()).Times(1);
//     EXPECT_CALL(blind0, open()).Times(0);
//     BlindMock blind1;
//     unsigned int id1 = 6;
//     ON_CALL(blind1, getId()).WillByDefault(Return(id1));
//     EXPECT_CALL(blind1, getId()).Times(1);
//     EXPECT_CALL(blind1, open()).Times(0);
//     LooperMock looper0;
//     LooperMock looper1;
//     IBlind *blinds[] = {&blind0, &blind1};
//     ILooper *loopers[] = {&looper0, &looper1};
//     unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
//     BlindsAccess access(blinds, loopers, numberOfBlinds);

//     access.open(7);
// }

// TEST(BlindsAccessTest, close_callsCloseOnCorrectBlind) {
//     BlindMock blind0;
//     unsigned int id0 = 5;
//     ON_CALL(blind0, getId()).WillByDefault(Return(id0));
//     EXPECT_CALL(blind0, getId()).Times(1);
//     EXPECT_CALL(blind0, close()).Times(1);
//     BlindMock blind1;
//     unsigned int id1 = 6;
//     ON_CALL(blind1, getId()).WillByDefault(Return(id1));
//     EXPECT_CALL(blind1, getId()).Times(1);
//     EXPECT_CALL(blind1, close()).Times(0);
//     LooperMock looper0;
//     LooperMock looper1;
//     IBlind *blinds[] = {&blind0, &blind1};
//     ILooper *loopers[] = {&looper0, &looper1};
//     unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
//     BlindsAccess access(blinds, loopers, numberOfBlinds);

//     access.close(id0);
// }

// TEST(BlindsAccessTest, close_doesNotCallCloseOnAnyBlindIfIdIsInvalid) {
//     BlindMock blind0;
//     unsigned int id0 = 5;
//     ON_CALL(blind0, getId()).WillByDefault(Return(id0));
//     EXPECT_CALL(blind0, getId()).Times(1);
//     EXPECT_CALL(blind0, close()).Times(0);
//     BlindMock blind1;
//     unsigned int id1 = 6;
//     ON_CALL(blind1, getId()).WillByDefault(Return(id1));
//     EXPECT_CALL(blind1, getId()).Times(1);
//     EXPECT_CALL(blind1, close()).Times(0);
//     LooperMock looper0;
//     LooperMock looper1;
//     IBlind *blinds[] = {&blind0, &blind1};
//     ILooper *loopers[] = {&looper0, &looper1};
//     unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
//     BlindsAccess access(blinds, loopers, numberOfBlinds);

//     access.close(7);
// }

// TEST(BlindsAccessTest, stop_callsStopOnCorrectBlind) {
//     BlindMock blind0;
//     unsigned int id0 = 5;
//     ON_CALL(blind0, getId()).WillByDefault(Return(id0));
//     EXPECT_CALL(blind0, getId()).Times(1);
//     EXPECT_CALL(blind0, stop()).Times(0);
//     BlindMock blind1;
//     unsigned int id1 = 6;
//     ON_CALL(blind1, getId()).WillByDefault(Return(id1));
//     EXPECT_CALL(blind1, getId()).Times(1);
//     EXPECT_CALL(blind1, stop()).Times(1);
//     LooperMock looper0;
//     LooperMock looper1;
//     IBlind *blinds[] = {&blind0, &blind1};
//     ILooper *loopers[] = {&looper0, &looper1};
//     unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
//     BlindsAccess access(blinds, loopers, numberOfBlinds);

//     access.stop(id1);
// }

// TEST(BlindsAccessTest, stop_doesNotCallStopOnAnyBlindIfIdIsInvalid) {
//     BlindMock blind0;
//     unsigned int id0 = 5;
//     ON_CALL(blind0, getId()).WillByDefault(Return(id0));
//     EXPECT_CALL(blind0, getId()).Times(1);
//     EXPECT_CALL(blind0, stop()).Times(0);
//     BlindMock blind1;
//     unsigned int id1 = 6;
//     ON_CALL(blind1, getId()).WillByDefault(Return(id1));
//     EXPECT_CALL(blind1, getId()).Times(1);
//     EXPECT_CALL(blind1, stop()).Times(0);
//     LooperMock looper0;
//     LooperMock looper1;
//     IBlind *blinds[] = {&blind0, &blind1};
//     ILooper *loopers[] = {&looper0, &looper1};
//     unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
//     BlindsAccess access(blinds, loopers, numberOfBlinds);

//     access.stop(7);
// }

// TEST(BlindsAccessTest, tilt_callsTiltOnCorrectBlind) {
//     BlindMock blind0;
//     unsigned int id0 = 5;
//     ON_CALL(blind0, getId()).WillByDefault(Return(id0));
//     EXPECT_CALL(blind0, getId()).Times(2);
//     EXPECT_CALL(blind0, tilt()).Times(1);
//     BlindMock blind1;
//     unsigned int id1 = 6;
//     ON_CALL(blind1, getId()).WillByDefault(Return(id1));
//     EXPECT_CALL(blind1, getId()).Times(2);
//     EXPECT_CALL(blind1, tilt()).Times(1);
//     LooperMock looper0;
//     LooperMock looper1;
//     IBlind *blinds[] = {&blind0, &blind1};
//     ILooper *loopers[] = {&looper0, &looper1};
//     unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
//     BlindsAccess access(blinds, loopers, numberOfBlinds);

//     access.tilt(id0);
//     access.tilt(id1);
// }

// TEST(BlindsAccessTest, tilt_doesNotCallTiltOnAnyBlindIfIdIsInvalid) {
//     BlindMock blind0;
//     unsigned int id0 = 5;
//     ON_CALL(blind0, getId()).WillByDefault(Return(id0));
//     EXPECT_CALL(blind0, getId()).Times(1);
//     EXPECT_CALL(blind0, tilt()).Times(0);
//     BlindMock blind1;
//     unsigned int id1 = 6;
//     ON_CALL(blind1, getId()).WillByDefault(Return(id1));
//     EXPECT_CALL(blind1, getId()).Times(1);
//     EXPECT_CALL(blind1, tilt()).Times(0);
//     LooperMock looper0;
//     LooperMock looper1;
//     IBlind *blinds[] = {&blind0, &blind1};
//     ILooper *loopers[] = {&looper0, &looper1};
//     unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
//     BlindsAccess access(blinds, loopers, numberOfBlinds);

//     access.tilt(7);
// }

// TEST(BlindsAccessTest, loop_callsLoopOnAllBlinds) {
//     BlindMock blind0;
//     BlindMock blind1;
//     LooperMock looper0;
//     EXPECT_CALL(looper0, loop()).Times(1);
//     LooperMock looper1;
//     EXPECT_CALL(looper1, loop()).Times(1);
//     IBlind *blinds[] = {&blind0, &blind1};
//     ILooper *loopers[] = {&looper0, &looper1};
//     unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
//     BlindsAccess access(blinds, loopers, numberOfBlinds);

//     access.loop();
// }
