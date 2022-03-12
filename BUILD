cc_library(
  name = "application",
  hdrs = ["src/BlindsControlView.h", "src/IDevice.h", "src/IDeviceData.h", "src/IHttpClient.h", "src/ISelectionButton.h", "src/IStatusBar.h", "src/ITouchButton.h"],
  srcs = ["src/BlindsControlView.cpp"],
)

cc_library(
  name = "simulators",
  hdrs = glob(["test/simulators/*.h"]),
  deps = ["application"],
)

cc_test(
  name = "tests",
  size = "small",
  srcs = glob(["test/*.cpp"]),
  deps = ["@com_google_googletest//:gtest_main", "simulators", "application"],
)