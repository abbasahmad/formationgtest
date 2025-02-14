load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "first_example",
    srcs = ["first_example.cc"],
    deps = [
        "//gmock_atm/bankserver:BankServerLib",
        "@googletest//:gtest_main",
    ],
)