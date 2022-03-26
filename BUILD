cc_library(
  name = "hmi",
  hdrs = glob(["src/hmi/*.h"]),
  srcs = glob(["src/hmi/*.cpp"]),
)


cc_library(
  name = "application",
  hdrs = ["src/IDevice.h", "src/IDeviceData.h", "src/IHttpClient.h", "src/HttpBlind.h", "src/BlindConfiguration.h", "src/HttpBlindHelper.h", "src/IBlinds.h", "src/BlindsAccess.h", "src/IBlind.h", "src/ILooper.h"],
  srcs = ["src/HttpBlind.cpp", "src/HttpBlindHelper.cpp", "src/BlindsAccess.cpp"],
)

cc_library(
  name = "simulators",
  hdrs = glob(["test/simulators/*.h"]),
  deps = ["application", "hmi"],
)

cc_test(
  name = "tests",
  size = "small",
  srcs = glob(["test/*.cpp"]),
  deps = ["@com_google_googletest//:gtest_main", "hmi", "simulators", "application"],
)