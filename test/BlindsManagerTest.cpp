#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/backend/BlindsManager.h"
#include "simulators/BlindsMock.h"
#include "simulators/DeviceMock.h"
#include "simulators/EnablableMock.h"
#include "simulators/LooperMock.h"

using ::testing::Return;

TEST(BlindsManagerTest, canCreateBlindsManager) {
    unsigned int blindIds[1];
    unsigned int numberOfIds = 0;
    EnablableMock enablable;
    BlindsMock blinds;
    LooperMock looper;

    BlindsManager manager(blindIds, numberOfIds, &enablable, &blinds, &looper);
}

TEST(BlindsManagerTest, loop_callsLoop) {
    unsigned int blindIds[1];
    unsigned int numberOfIds = 0;
    EnablableMock enablable;
    BlindsMock blinds;
    LooperMock looper;
    EXPECT_CALL(looper, loop()).Times(1);

    BlindsManager manager(blindIds, numberOfIds, &enablable, &blinds, &looper);
    manager.loop();
}

TEST(BlindsManagerTest, enable_callsEnableForCorrectIds) {
    unsigned int blindIds[] = {42, 69};
    unsigned int numberOfIds = sizeof(blindIds) / sizeof(blindIds[0]);
    EnablableMock enablable;
    EXPECT_CALL(enablable, enable(blindIds[0])).Times(1);
    EXPECT_CALL(enablable, enable(blindIds[1])).Times(1);
    BlindsMock blinds;
    LooperMock looper;

    BlindsManager manager(blindIds, numberOfIds, &enablable, &blinds, &looper);

    manager.enable(blindIds[0]);
    manager.enable(blindIds[1]);
}

TEST(BlindsManagerTest, disable_callsDisableForCorrectIds) {
    unsigned int blindIds[] = {42, 69};
    unsigned int numberOfIds = sizeof(blindIds) / sizeof(blindIds[0]);
    EnablableMock enablable;
    EXPECT_CALL(enablable, disable(blindIds[0])).Times(1);
    EXPECT_CALL(enablable, disable(blindIds[1])).Times(1);
    BlindsMock blinds;
    LooperMock looper;

    BlindsManager manager(blindIds, numberOfIds, &enablable, &blinds, &looper);

    manager.disable(blindIds[0]);
    manager.disable(blindIds[1]);
}

TEST(BlindsManagerTest, isEnabled_getsCorrectStateForId) {
    unsigned int blindIds[] = {42, 69};
    unsigned int numberOfIds = sizeof(blindIds) / sizeof(blindIds[0]);
    bool blindStates[] = {true, false};
    EnablableMock enablable;
    ON_CALL(enablable, isEnabled(blindIds[0]))
        .WillByDefault(Return(blindStates[0]));
    EXPECT_CALL(enablable, isEnabled(blindIds[0])).Times(1);
    ON_CALL(enablable, isEnabled(blindIds[1]))
        .WillByDefault(Return(blindStates[1]));
    EXPECT_CALL(enablable, isEnabled(blindIds[1])).Times(1);
    BlindsMock blinds;
    LooperMock looper;

    BlindsManager manager(blindIds, numberOfIds, &enablable, &blinds, &looper);

    EXPECT_EQ(blindStates[0], manager.isEnabled(blindIds[0]));
    EXPECT_EQ(blindStates[1], manager.isEnabled(blindIds[1]));
}

TEST(BlindsManagerTest, open_callsOpenOnEnabledBlinds) {
    unsigned int blindIds[] = {42, 69};
    unsigned int numberOfIds = sizeof(blindIds) / sizeof(blindIds[0]);
    bool blindStates[] = {true, false};
    EnablableMock enablable;
    ON_CALL(enablable, isEnabled(blindIds[0]))
        .WillByDefault(Return(blindStates[0]));
    EXPECT_CALL(enablable, isEnabled(blindIds[0])).Times(1);
    ON_CALL(enablable, isEnabled(blindIds[1]))
        .WillByDefault(Return(blindStates[1]));
    EXPECT_CALL(enablable, isEnabled(blindIds[1])).Times(1);
    BlindsMock blinds;
    EXPECT_CALL(blinds, open(blindIds[0])).Times(1);
    EXPECT_CALL(blinds, open(blindIds[1])).Times(0);
    LooperMock looper;

    BlindsManager manager(blindIds, numberOfIds, &enablable, &blinds, &looper);

    manager.open();
}

TEST(BlindsManagerTest, close_callsCloseOnEnabledBlinds) {
    unsigned int blindIds[] = {42, 69};
    unsigned int numberOfIds = sizeof(blindIds) / sizeof(blindIds[0]);
    bool blindStates[] = {true, true};
    EnablableMock enablable;
    ON_CALL(enablable, isEnabled(blindIds[0]))
        .WillByDefault(Return(blindStates[0]));
    EXPECT_CALL(enablable, isEnabled(blindIds[0])).Times(1);
    ON_CALL(enablable, isEnabled(blindIds[1]))
        .WillByDefault(Return(blindStates[1]));
    EXPECT_CALL(enablable, isEnabled(blindIds[1])).Times(1);
    BlindsMock blinds;
    EXPECT_CALL(blinds, close(blindIds[0])).Times(1);
    EXPECT_CALL(blinds, close(blindIds[1])).Times(1);
    LooperMock looper;

    BlindsManager manager(blindIds, numberOfIds, &enablable, &blinds, &looper);

    manager.close();
}

TEST(BlindsManagerTest, stop_callsStopOnEnabledBlinds) {
    unsigned int blindIds[] = {42, 69};
    unsigned int numberOfIds = sizeof(blindIds) / sizeof(blindIds[0]);
    bool blindStates[] = {false, true};
    EnablableMock enablable;
    ON_CALL(enablable, isEnabled(blindIds[0]))
        .WillByDefault(Return(blindStates[0]));
    EXPECT_CALL(enablable, isEnabled(blindIds[0])).Times(1);
    ON_CALL(enablable, isEnabled(blindIds[1]))
        .WillByDefault(Return(blindStates[1]));
    EXPECT_CALL(enablable, isEnabled(blindIds[1])).Times(1);
    BlindsMock blinds;
    EXPECT_CALL(blinds, stop(blindIds[0])).Times(0);
    EXPECT_CALL(blinds, stop(blindIds[1])).Times(1);
    LooperMock looper;

    BlindsManager manager(blindIds, numberOfIds, &enablable, &blinds, &looper);

    manager.stop();
}

TEST(BlindsManagerTest, tilt_callsTiltOnEnabledBlinds) {
    unsigned int blindIds[] = {42, 69};
    unsigned int numberOfIds = sizeof(blindIds) / sizeof(blindIds[0]);
    bool blindStates[] = {false, true};
    EnablableMock enablable;
    ON_CALL(enablable, isEnabled(blindIds[0]))
        .WillByDefault(Return(blindStates[0]));
    EXPECT_CALL(enablable, isEnabled(blindIds[0])).Times(1);
    ON_CALL(enablable, isEnabled(blindIds[1]))
        .WillByDefault(Return(blindStates[1]));
    EXPECT_CALL(enablable, isEnabled(blindIds[1])).Times(1);
    BlindsMock blinds;
    EXPECT_CALL(blinds, tilt(blindIds[0])).Times(0);
    EXPECT_CALL(blinds, tilt(blindIds[1])).Times(1);
    LooperMock looper;

    BlindsManager manager(blindIds, numberOfIds, &enablable, &blinds, &looper);

    manager.tilt();
}
