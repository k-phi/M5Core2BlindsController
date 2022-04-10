#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/backend/BlindsAccess.h"
#include "simulators/BlindMock.h"
#include "simulators/LooperMock.h"

using ::testing::Return;

TEST(BlindsAccessTest, canCreateBlindsAccess) {
    BlindMock blind0;
    BlindMock blind1;
    LooperMock looper0;
    LooperMock looper1;
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);
}

TEST(BlindsAccessTest, open_callsOpenOnCorrectBlind) {
    BlindMock blind0;
    unsigned int id0 = 5;
    ON_CALL(blind0, getId()).WillByDefault(Return(id0));
    EXPECT_CALL(blind0, getId()).Times(1);
    EXPECT_CALL(blind0, open()).Times(0);
    BlindMock blind1;
    unsigned int id1 = 6;
    ON_CALL(blind1, getId()).WillByDefault(Return(id1));
    EXPECT_CALL(blind1, getId()).Times(1);
    EXPECT_CALL(blind1, open()).Times(1);
    LooperMock looper0;
    LooperMock looper1;
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);

    access.open(id1);
}

TEST(BlindsAccessTest, open_doesNotCallOpenOnAnyBlindIfIdIsInvalid) {
    BlindMock blind0;
    unsigned int id0 = 5;
    ON_CALL(blind0, getId()).WillByDefault(Return(id0));
    EXPECT_CALL(blind0, getId()).Times(1);
    EXPECT_CALL(blind0, open()).Times(0);
    BlindMock blind1;
    unsigned int id1 = 6;
    ON_CALL(blind1, getId()).WillByDefault(Return(id1));
    EXPECT_CALL(blind1, getId()).Times(1);
    EXPECT_CALL(blind1, open()).Times(0);
    LooperMock looper0;
    LooperMock looper1;
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);

    access.open(7);
}

TEST(BlindsAccessTest, close_callsCloseOnCorrectBlind) {
    BlindMock blind0;
    unsigned int id0 = 5;
    ON_CALL(blind0, getId()).WillByDefault(Return(id0));
    EXPECT_CALL(blind0, getId()).Times(1);
    EXPECT_CALL(blind0, close()).Times(1);
    BlindMock blind1;
    unsigned int id1 = 6;
    ON_CALL(blind1, getId()).WillByDefault(Return(id1));
    EXPECT_CALL(blind1, getId()).Times(1);
    EXPECT_CALL(blind1, close()).Times(0);
    LooperMock looper0;
    LooperMock looper1;
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);

    access.close(id0);
}

TEST(BlindsAccessTest, close_doesNotCallCloseOnAnyBlindIfIdIsInvalid) {
    BlindMock blind0;
    unsigned int id0 = 5;
    ON_CALL(blind0, getId()).WillByDefault(Return(id0));
    EXPECT_CALL(blind0, getId()).Times(1);
    EXPECT_CALL(blind0, close()).Times(0);
    BlindMock blind1;
    unsigned int id1 = 6;
    ON_CALL(blind1, getId()).WillByDefault(Return(id1));
    EXPECT_CALL(blind1, getId()).Times(1);
    EXPECT_CALL(blind1, close()).Times(0);
    LooperMock looper0;
    LooperMock looper1;
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);

    access.close(7);
}

TEST(BlindsAccessTest, stop_callsStopOnCorrectBlind) {
    BlindMock blind0;
    unsigned int id0 = 5;
    ON_CALL(blind0, getId()).WillByDefault(Return(id0));
    EXPECT_CALL(blind0, getId()).Times(1);
    EXPECT_CALL(blind0, stop()).Times(0);
    BlindMock blind1;
    unsigned int id1 = 6;
    ON_CALL(blind1, getId()).WillByDefault(Return(id1));
    EXPECT_CALL(blind1, getId()).Times(1);
    EXPECT_CALL(blind1, stop()).Times(1);
    LooperMock looper0;
    LooperMock looper1;
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);

    access.stop(id1);
}

TEST(BlindsAccessTest, stop_doesNotCallStopOnAnyBlindIfIdIsInvalid) {
    BlindMock blind0;
    unsigned int id0 = 5;
    ON_CALL(blind0, getId()).WillByDefault(Return(id0));
    EXPECT_CALL(blind0, getId()).Times(1);
    EXPECT_CALL(blind0, stop()).Times(0);
    BlindMock blind1;
    unsigned int id1 = 6;
    ON_CALL(blind1, getId()).WillByDefault(Return(id1));
    EXPECT_CALL(blind1, getId()).Times(1);
    EXPECT_CALL(blind1, stop()).Times(0);
    LooperMock looper0;
    LooperMock looper1;
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);

    access.stop(7);
}

TEST(BlindsAccessTest, tilt_callsTiltOnCorrectBlind) {
    BlindMock blind0;
    unsigned int id0 = 5;
    ON_CALL(blind0, getId()).WillByDefault(Return(id0));
    EXPECT_CALL(blind0, getId()).Times(2);
    EXPECT_CALL(blind0, tilt()).Times(1);
    BlindMock blind1;
    unsigned int id1 = 6;
    ON_CALL(blind1, getId()).WillByDefault(Return(id1));
    EXPECT_CALL(blind1, getId()).Times(2);
    EXPECT_CALL(blind1, tilt()).Times(1);
    LooperMock looper0;
    LooperMock looper1;
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);

    access.tilt(id0);
    access.tilt(id1);
}

TEST(BlindsAccessTest, tilt_doesNotCallTiltOnAnyBlindIfIdIsInvalid) {
    BlindMock blind0;
    unsigned int id0 = 5;
    ON_CALL(blind0, getId()).WillByDefault(Return(id0));
    EXPECT_CALL(blind0, getId()).Times(1);
    EXPECT_CALL(blind0, tilt()).Times(0);
    BlindMock blind1;
    unsigned int id1 = 6;
    ON_CALL(blind1, getId()).WillByDefault(Return(id1));
    EXPECT_CALL(blind1, getId()).Times(1);
    EXPECT_CALL(blind1, tilt()).Times(0);
    LooperMock looper0;
    LooperMock looper1;
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);

    access.tilt(7);
}

TEST(BlindsAccessTest, loop_callsLoopOnAllBlinds) {
    BlindMock blind0;
    BlindMock blind1;
    LooperMock looper0;
    EXPECT_CALL(looper0, loop()).Times(1);
    LooperMock looper1;
    EXPECT_CALL(looper1, loop()).Times(1);
    IBlind *blinds[] = {&blind0, &blind1};
    ILooper *loopers[] = {&looper0, &looper1};
    unsigned int numberOfBlinds = sizeof(blinds) / sizeof(blinds[0]);
    BlindsAccess access(blinds, loopers, numberOfBlinds);

    access.loop();
}
