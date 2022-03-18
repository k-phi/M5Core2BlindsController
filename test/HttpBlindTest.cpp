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
    long timeoutInMilliseconds = 100;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);
}

TEST(HttpBlindTest, loop_sendsOpenOnceOnSuccess) {
    BlindConfiguration config = createConfig();
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    EXPECT_CALL(*httpClient, begin(_)).Times(1);
    EXPECT_CALL(*httpClient, sendRequest(StrEq("GET"))).Times(1);
    EXPECT_CALL(*httpClient, end()).Times(1);
    ON_CALL(*httpClient, sendRequest(_)).WillByDefault(Return(200));
    long timeoutInMilliseconds = 10;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);
    
    blind.open();
    blind.loop();
    std::this_thread::sleep_for(std::chrono::milliseconds(timeoutInMilliseconds + 2));
    blind.loop();
}
