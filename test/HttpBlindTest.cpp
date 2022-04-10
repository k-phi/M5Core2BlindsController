#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "../src/BlindConfiguration.h"
#include "../src/HttpBlind.h"
#include "../src/IBlind.h"
#include "../src/ILooper.h"
#include "simulators/HttpClientWrapperMock.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::SetArrayArgument;
using ::testing::StrEq;

BlindConfiguration createConfig() {
    BlindConfiguration config;
    config.Id = 5;
    config.iP = "255.255.255.255";
    config.canTilt = true;
    config.tiltPositionInPercent = 2.0f;
    return config;
}

TEST(HttpBlindTest, canCreateHttpBlind) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);
}

TEST(HttpBlindTest, getId_returnsCorrectId) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);
    EXPECT_EQ(config.Id, blind.getId());
}

TEST(HttpBlindTest, loop_sendsOpenOnceIfSentSuccessfully) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=open")))
        .Times(1);
    EXPECT_CALL(httpClient, sendRequest(StrEq("GET"))).Times(1);
    EXPECT_CALL(httpClient, end()).Times(1);
    ON_CALL(httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.open();
    blind.loop();  // sends open
    blind.loop();  // sends nothing
}

TEST(HttpBlindTest, loop_sendsOpenAgainIfSendingFailed) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=open")))
        .Times(2);
    EXPECT_CALL(httpClient, sendRequest(StrEq("GET")))
        .Times(2)
        .WillOnce(Return(500))
        .WillOnce(Return(200));
    EXPECT_CALL(httpClient, end()).Times(2);
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.open();
    blind.loop();  // sends open but fails
    blind.loop();  // sends open
    blind.loop();  // sends nothing
}

TEST(HttpBlindTest, loop_sendsNothingIfAlreadyOpening) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=open")))
        .Times(1);
    EXPECT_CALL(httpClient, sendRequest(StrEq("GET"))).Times(1);
    EXPECT_CALL(httpClient, end()).Times(1);
    ON_CALL(httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.open();
    blind.loop();  //  sends open

    blind.open();
    blind.loop();  // sends nothing
}

TEST(HttpBlindTest, loop_sendsCloseOnceIfSentSuccessfully) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=close")))
        .Times(1);
    EXPECT_CALL(httpClient, sendRequest(StrEq("GET"))).Times(1);
    EXPECT_CALL(httpClient, end()).Times(1);
    ON_CALL(httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.close();
    blind.loop();  // sends close
    blind.loop();  // sends nothing
}

TEST(HttpBlindTest, loop_sendsCloseAgainIfSendingFailed) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=close")))
        .Times(2);
    EXPECT_CALL(httpClient, sendRequest(StrEq("GET")))
        .Times(2)
        .WillOnce(Return(500))
        .WillOnce(Return(200));
    EXPECT_CALL(httpClient, end()).Times(2);
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.close();
    blind.loop();  // sends close but fails
    blind.loop();  // sends close again
    blind.loop();  // sends nothing
}

TEST(HttpBlindTest, loop_sendsNothingIfAlreadyClosing) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=close")))
        .Times(1);
    EXPECT_CALL(httpClient, sendRequest(StrEq("GET"))).Times(1);
    EXPECT_CALL(httpClient, end()).Times(1);
    ON_CALL(httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.close();
    blind.loop();  // sends close

    blind.close();
    blind.loop();  // sends nothing
}

TEST(HttpBlindTest, loop_sendsStopOnceIfSentSuccessfully) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=open")))
        .Times(1);
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=stop")))
        .Times(1);
    EXPECT_CALL(httpClient, sendRequest(StrEq("GET"))).Times(2);
    EXPECT_CALL(httpClient, end()).Times(2);
    ON_CALL(httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.open();
    blind.loop();  // sends open

    blind.stop();
    blind.loop();  // sends stop
    blind.loop();  // sends nothing
}

TEST(HttpBlindTest, loop_sendsStopAgainIfSendingFailed) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=close")))
        .Times(1);
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=stop")))
        .Times(2);
    EXPECT_CALL(httpClient, sendRequest(StrEq("GET")))
        .Times(3)
        .WillOnce(Return(200))
        .WillOnce(Return(500))
        .WillOnce(Return(200));
    EXPECT_CALL(httpClient, end()).Times(3);
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.close();
    blind.loop();  // sends close

    blind.stop();
    blind.loop();  // sends stop but fails
    blind.loop();  // sends stop again
    blind.loop();  // sendds nothing
}

TEST(HttpBlindTest, loop_sendsNothingIfNotMoving) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient, begin(_)).Times(0);
    EXPECT_CALL(httpClient, sendRequest(_)).Times(0);
    EXPECT_CALL(httpClient, end()).Times(0);
    ON_CALL(httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.stop();
    blind.loop();  // sends nothing
}

TEST(HttpBlindTest, loop_sendsNothingForTiltIfBlindCannotTilt) {
    BlindConfiguration config = createConfig();
    config.canTilt = false;
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient, begin(_)).Times(0);
    EXPECT_CALL(httpClient, sendRequest(_)).Times(0);
    EXPECT_CALL(httpClient, end()).Times(0);
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.tilt();
    blind.loop();  // sends nothing
}

TEST(HttpBlindTest, loop_sendsCorrectCommandSequenceForTilt) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient,
                begin(StrEq("http://255.255.255.255/roller/0?go=close")))
        .Times(1);
    EXPECT_CALL(httpClient, begin(StrEq("http://255.255.255.255/roller/0")))
        .Times(1);
    EXPECT_CALL(
        httpClient,
        begin(StrEq("http://255.255.255.255/roller/0?go=to_pos&roller_pos=2")))
        .Times(1);
    EXPECT_CALL(httpClient, sendRequest(StrEq("GET"))).Times(3);
    EXPECT_CALL(httpClient, end()).Times(3);
    ON_CALL(httpClient, sendRequest(_)).WillByDefault(Return(200));
    char payload[] =
        "{\"state\":\"stop\",\"source\":\"schedule\",\"power\":0.00,\"is_"
        "valid\":true,\"safety_switch\":false,\"overtemperature\":false,\"stop_"
        "reason\":\"normal\",\"last_direction\":\"close\",\"current_pos\":0,"
        "\"calibrating\":false,\"positioning\":true}";
    int payloadLenght = sizeof(payload) / sizeof(payload[0]);
    EXPECT_CALL(httpClient, getPayload(_))
        .WillOnce(SetArrayArgument<0>(payload, payload + payloadLenght));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, &httpClient, timeoutInMilliseconds);

    blind.tilt();
    blind.loop();  // sends close
    std::this_thread::sleep_for(
        std::chrono::milliseconds(timeoutInMilliseconds + 2));
    blind.loop();  // gets stopped and sends open
    blind.loop();  // sends nothing
}
