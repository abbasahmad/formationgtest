// Filtrer vos tests.
// Utilisez ces commandes pour executer:
// bazel test test:filtered_tests_test --test_arg=--gtest_filter=*.My*
// OU
// bazel test test:filtered_tests_test --test_filter=*.My*

#include "gtest/gtest.h"



TEST(BasicChecks, MyTest1) { EXPECT_TRUE(true); }

TEST(BasicChecks, MyTest2) { EXPECT_TRUE(true); }

TEST(BasicChecks, YourTest1) { EXPECT_TRUE(false); }

TEST(BasicChecks, YourTest2) { EXPECT_TRUE(false); }
