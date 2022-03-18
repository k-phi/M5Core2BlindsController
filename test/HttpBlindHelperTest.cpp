#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/HttpBlindHelper.h"

TEST(HttpBlindHelperTest, getStateStringFromPayload_getsOpen) {
    const char *payload = "{\"state\":\"open\",\"source\":\"schedule\",\"power\":0.00,\"is_valid\":true,\"safety_switch\":false,\"overtemperature\":false,\"stop_reason\":\"normal\",\"last_direction\":\"close\",\"current_pos\":0,\"calibrating\":false,\"positioning\":true}";
    HttpBlindHelper helper;
    char stateString[40];
    helper.getStateStringFromPayload(stateString, payload);
    EXPECT_STREQ("open", stateString);
}

TEST(HttpBlindHelperTest, getStateStringFromPayload_getsClose) {
    const char *payload = "{\"state\":\"close\",\"source\":\"schedule\",\"power\":0.00,\"is_valid\":true,\"safety_switch\":false,\"overtemperature\":false,\"stop_reason\":\"normal\",\"last_direction\":\"close\",\"current_pos\":0,\"calibrating\":false,\"positioning\":true}";
    HttpBlindHelper helper;
    char stateString[40];
    helper.getStateStringFromPayload(stateString, payload);
    EXPECT_STREQ("close", stateString);
}

TEST(HttpBlindHelperTest, getStateStringFromPayload_getsStop) {
    const char *payload = "{\"state\":\"stop\",\"source\":\"schedule\",\"power\":0.00,\"is_valid\":true,\"safety_switch\":false,\"overtemperature\":false,\"stop_reason\":\"normal\",\"last_direction\":\"close\",\"current_pos\":0,\"calibrating\":false,\"positioning\":true}";
    HttpBlindHelper helper;
    char stateString[40];
    helper.getStateStringFromPayload(stateString, payload);
    EXPECT_STREQ("stop", stateString);
}
