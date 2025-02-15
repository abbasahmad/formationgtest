load("@rules_cc//cc:defs.bzl", "cc_test", "cc_binary")


#cc_test(
#    name = "all_cc_tests",
#    size="small",
#    srcs = glob(["*_test.cc"]),  # Execution de tout les fichiers qui finissent par "_test.cc"
#    deps = [
#        "@googletest//:gtest_main",
#        "//src/lib:CPPLib",
#    ],
#)


cc_test(
    name = "premiers_test",
    size ="small",
    srcs = ["premiers_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_binary(
    name = "premiers_test_main",
    srcs = ["premiers_test_main.cc"],
    #copts = ["--std=c++17"],
    deps = [
        "@googletest//:gtest",
    ],
)


cc_test(
    name = "fib_test",
    size ="small",
    srcs = ["fib_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        #"//src/lib:CPPLib",
    ],
)



cc_test(
    name = "assertions_communes_test",
    srcs = ["assertions_communes_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "assert_vs_expect_test",
    srcs = ["assert_vs_expect_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "c_string_test",
    srcs = ["c_string_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "floating_points_test",
    srcs = ["floating_points_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "predicate_test",
    srcs = ["predicate_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "exceptions_test",
    srcs = ["exceptions_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "disabled_tests_test",
    srcs = ["disabled_tests_test.cc"],
    size = "small",
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "private_members_test",
    srcs = ["private_members_test.cc"],
    size = "small",
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "filtered_tests_test",
    srcs = ["filtered_tests_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "typed_tests_findmax_test",
    srcs = ["typed_tests_findmax_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "death_test",
    srcs = ["death_test.cc"],
    size ="small",
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "fixture_test",
    srcs = ["fixture_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "function_test",
    srcs = ["function_test.cc"],
    size = "small",
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "tests_param_test",
    srcs = ["tests_param_test.cc"],
    size = "small",
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "share_logic_test",
    srcs = ["share_logic_test.cc"],
    size ="small",
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "tests_param_combine_test",
    srcs = ["tests_param_combine_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "user_types_test",
    srcs = ["user_types_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "adding_traces_test",
    srcs = ["adding_traces_test.cc"],
    deps = [
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "tests_param_combine_name_generator_test",
    srcs = ["tests_param_combine_name_generator_test.cc"],
    size = "small",
    deps = [
        "@googletest//:gtest_main",
    ],
)


cc_test(
    name = "typed_prameterized_tests_findmax_test",
    srcs = ["typed_prameterized_tests_findmax_test.cc"],
    size = "small",
    deps = [
        "@googletest//:gtest_main",
    ],
)