cc_library(
  name = "application",
  hdrs = glob(["src/*.h"]),
  srcs = glob(["src/*.cpp"]),
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