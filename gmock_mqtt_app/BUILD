load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "MqttClient_test",
    srcs = ["MqttClient_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        "//src/mqtt_app:MqttClientLib",
    ],
)

cc_test(
    name = "MqttClient_Fixture_test",
    srcs = ["MqttClient_Fixture_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        "//src/mqtt_app:MqttClientLib",
    ],
)