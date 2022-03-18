#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/HttpBlindHelper.h"

TEST(HttpBlindHelperTest, getStateStringFromPayload_getsOpen) {
    const char *payload = "{\"state\":\"open\",\"source\":\"schedule\"}";
    HttpBlindHelper helper;
    char stateString[40];
    helper.getStateStringFromPayload(stateString, payload);
    EXPECT_STREQ("open", stateString);
}

TEST(HttpBlindHelperTest, getStateStringFromPayload_getsClose) {
    const char *payload = "{\"state\":\"close\",\"source\":\"schedule\"}";
    HttpBlindHelper helper;
    char stateString[40];
    helper.getStateStringFromPayload(stateString, payload);
    EXPECT_STREQ("close", stateString);
}

TEST(HttpBlindHelperTest, getStateStringFromPayload_getsStop) {
    const char *payload = "{\"state\":\"open\",\"source\":\"schedule\"}";
    HttpBlindHelper helper;
    char stateString[40];
    helper.getStateStringFromPayload(stateString, payload);
    EXPECT_STREQ("open", stateString);
}
