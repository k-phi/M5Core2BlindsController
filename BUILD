cc_library(
  name = "application",
  hdrs = ["src/BlindConfiguration.h"],
)

cc_library(
  name = "backend",
  hdrs = glob(["src/backend/*.h"]),
  srcs = glob(["src/backend/*.cpp"]),
  deps = ["application"],
)

cc_library(
  name = "hmi",
  hdrs = glob(["src/hmi/*.h"]),
  srcs = glob(["src/hmi/*.cpp"]),
  deps = ["backend"],
)

cc_library(
  name = "simulators",
  hdrs = glob(["test/simulators/*.h"]),
  deps = ["hmi"],
)

cc_test(
  name = "tests",
  size = "small",
  srcs = glob(["test/*.cpp"]),
  deps = ["@com_google_googletest//:gtest_main", "simulators"],
)