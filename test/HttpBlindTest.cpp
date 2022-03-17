#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/BlindConfiguration.h"
#include "../src/HttpBlind.h"
#include "simulators/HttpClientWrapperMock.h"

using ::testing::_;
using ::testing::AtLeast;

TEST(HttpBlindTest, canCreateHttpBlind) {
    BlindConfiguration config;
    config.Id = 5;
    config.iP = "255.255.255.255";
    config.canTilt = true;
    config.tiltPositionInPercent = 2.0f;
    HttpClientWrapperMock *httpClient = new HttpClientWrapperMock();
    long timeoutInMilliseconds = 100;
    HttpBlind blind(config, httpClient, timeoutInMilliseconds);
}
