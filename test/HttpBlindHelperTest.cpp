#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/backend/HttpBlindHelper.h"

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

TEST(HttpBlindHelperTest, getStateUrl_returnsCorrectUrl) {
    const char *payload = "255.255.255.255";
    HttpBlindHelper helper;
    char url[200];
    helper.getStateUrl(url, payload);
    EXPECT_STREQ("http://255.255.255.255/roller/0", url);
}

TEST(HttpBlindHelperTest, getOpenUrl_returnsCorrectUrl) {
    const char *payload = "255.255.255.255";
    HttpBlindHelper helper;
    char url[200];
    helper.getOpenUrl(url, payload);
    EXPECT_STREQ("http://255.255.255.255/roller/0?go=open", url);
}

TEST(HttpBlindHelperTest, getCloseUrl_returnsCorrectUrl) {
    const char *payload = "255.255.255.255";
    HttpBlindHelper helper;
    char url[200];
    helper.getCloseUrl(url, payload);
    EXPECT_STREQ("http://255.255.255.255/roller/0?go=close", url);
}

TEST(HttpBlindHelperTest, getStopUrl_returnsCorrectUrl) {
    const char *payload = "255.255.255.255";
    HttpBlindHelper helper;
    char url[200];
    helper.getStopUrl(url, payload);
    EXPECT_STREQ("http://255.255.255.255/roller/0?go=stop", url);
}

TEST(HttpBlindHelperTest, getGoToUrl_returnsCorrectUrl) {
    const char *payload = "255.255.255.255";
    HttpBlindHelper helper;
    char url[200];
    helper.getGoToUrl(url, payload, 2.000f);
    EXPECT_STREQ("http://255.255.255.255/roller/0?go=to_pos&roller_pos=2", url);
}
