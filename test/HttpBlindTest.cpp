#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "../src/BlindConfiguration.h"
#include "../src/HttpBlind.h"
#include "simulators/HttpClientWrapperMock.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::StrEq;
using ::testing::Return;
using ::testing::SetArrayArgument;

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
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);
}

TEST(HttpBlindTest, loop_sendsOpenOnceOnSuccess) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    EXPECT_CALL(*httpClient, begin(StrEq("http://255.255.255.255/roller/0/go=open"))).Times(1);
    EXPECT_CALL(*httpClient, sendRequest(StrEq("GET"))).Times(1);
    EXPECT_CALL(*httpClient, end()).Times(1);
    ON_CALL(*httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);

    blind.open();
    blind.loop();
    blind.loop();
}

TEST(HttpBlindTest, loop_sendsOpenAgainOnFailure) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    EXPECT_CALL(*httpClient, begin(StrEq("http://255.255.255.255/roller/0/go=open"))).Times(2);
    EXPECT_CALL(*httpClient, sendRequest(StrEq("GET"))).Times(2);
    EXPECT_CALL(*httpClient, end()).Times(2);
    ON_CALL(*httpClient, sendRequest(_)).WillByDefault(Return(500));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);
    
    blind.open();
    blind.loop();
    blind.loop();
}

TEST(HttpBlindTest, loop_sendsCloseOnceOnSuccess) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    EXPECT_CALL(*httpClient, begin(StrEq("http://255.255.255.255/roller/0/go=close"))).Times(1);
    EXPECT_CALL(*httpClient, sendRequest(StrEq("GET"))).Times(1);
    EXPECT_CALL(*httpClient, end()).Times(1);
    ON_CALL(*httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);

    blind.close();
    blind.loop();
    blind.loop();
}

TEST(HttpBlindTest, loop_sendsCloseAgainOnFailure) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    EXPECT_CALL(*httpClient, begin(StrEq("http://255.255.255.255/roller/0/go=close"))).Times(2);
    EXPECT_CALL(*httpClient, sendRequest(StrEq("GET"))).Times(2);
    EXPECT_CALL(*httpClient, end()).Times(2);
    ON_CALL(*httpClient, sendRequest(_)).WillByDefault(Return(500));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);
    
    blind.close();
    blind.loop();
    blind.loop();
}

TEST(HttpBlindTest, loop_sendsStopOnceOnSuccess) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    EXPECT_CALL(*httpClient, begin(StrEq("http://255.255.255.255/roller/0/go=stop"))).Times(1);
    EXPECT_CALL(*httpClient, sendRequest(StrEq("GET"))).Times(1);
    EXPECT_CALL(*httpClient, end()).Times(1);
    ON_CALL(*httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);

    blind.stop();
    blind.loop();
    blind.loop();
}

TEST(HttpBlindTest, loop_sendsStopAgainOnFailure) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    EXPECT_CALL(*httpClient, begin(StrEq("http://255.255.255.255/roller/0/go=stop"))).Times(2);
    EXPECT_CALL(*httpClient, sendRequest(StrEq("GET"))).Times(2);
    EXPECT_CALL(*httpClient, end()).Times(2);
    ON_CALL(*httpClient, sendRequest(_)).WillByDefault(Return(500));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);
    
    blind.stop();
    blind.loop();
    blind.loop();
}

TEST(HttpBlindTest, loop_sendsNothingForTiltIfBlindCannotTilt) {
    BlindConfiguration config = createConfig();
    config.canTilt = false;
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    EXPECT_CALL(*httpClient, begin(_)).Times(0);
    EXPECT_CALL(*httpClient, sendRequest(_)).Times(0);
    EXPECT_CALL(*httpClient, end()).Times(0);
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);
    
    blind.tilt();
    blind.loop();
}

TEST(HttpBlindTest, loop_sendsCorrectCommandSequenceForTilt) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    EXPECT_CALL(*httpClient, begin(_)).Times(3);
    EXPECT_CALL(*httpClient, sendRequest(StrEq("GET"))).Times(3);
    EXPECT_CALL(*httpClient, end()).Times(3);
    ON_CALL(*httpClient, sendRequest(_)).WillByDefault(Return(200));
    char payload[] = "{\"state\":\"stop\",\"source\":\"schedule\",\"power\":0.00,\"is_valid\":true,\"safety_switch\":false,\"overtemperature\":false,\"stop_reason\":\"normal\",\"last_direction\":\"close\",\"current_pos\":0,\"calibrating\":false,\"positioning\":true}";
    int payloadLenght = sizeof(payload)/sizeof(payload[0]);
    EXPECT_CALL(*httpClient, getPayload(_)).WillOnce(SetArrayArgument<0>(payload, payload + payloadLenght));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);
    
    blind.tilt();
    blind.loop();
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutInMilliseconds + 2));
    blind.loop();
}
