#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "simulators/DeviceMock.h"
#include "simulators/HttpClientWrapperMock.h"
#include "simulators/DeviceDataMock.h"

using ::testing::AtLeast;
using ::testing::_;

TEST(DeviceTest, setWifiSsidIsCalled) {
    DeviceMock device;
    EXPECT_CALL(device, isWiFiConnected()).Times(AtLeast(1));

    device.isWiFiConnected();
}

TEST(HttpClientTest, beginIsCalled) {
    HttpClientWrapperMock httpClient;
    EXPECT_CALL(httpClient, begin(_)).Times(AtLeast(1));

    const char* url = "foo";
    httpClient.begin(url);
}

TEST(DeviceDataTest, saveBoolIsCalled) {
    DeviceDataMock deviceData;
    EXPECT_CALL(deviceData, saveBool(_,_)).Times(AtLeast(1));
    
    deviceData.saveBool("foo", true);
}