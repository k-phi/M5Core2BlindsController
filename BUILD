cc_library(
  name = "firmware_abstraction_interfaces",
  hdrs = ["src/IDevice.h", "src/IHttpClient.h", "src/IDeviceData.h", "src/UiControlBase.h", "src/IStatusBar.h", "src/ITouchButton.h"],
)

cc_library(
  name = "simulators",
  hdrs = glob(["test/simulators/*.h"]),
  deps = ["firmware_abstraction_interfaces"],
)

cc_test(
  name = "tests",
  size = "small",
  srcs = glob(["test/*.cpp"]),
  deps = ["@com_google_googletest//:gtest_main", "simulators"],
)