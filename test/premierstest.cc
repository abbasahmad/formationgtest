#include "gtest/gtest.h"

TEST(PremiersTest, AssertionBasiquesEgale) {
  EXPECT_EQ("Google", "Google");
  EXPECT_EQ(1, 1);
  EXPECT_EQ(7 * 6, 42);
}

TEST(PremiersTest, AssertionBasiquesNonEgale) {
  EXPECT_STRNE("Google", "Test");
  EXPECT_NE(1, 2);
  EXPECT_NE(7 * 6, 37);
}