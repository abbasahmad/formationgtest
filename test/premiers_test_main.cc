#include "gtest/gtest.h"

TEST(PremiersTestMain, AssertionBasiquesEgale) {
  EXPECT_EQ("Google", "Google") << "Ma condition n'est pas vraie" << std::endl;
  EXPECT_EQ(1,1);
  EXPECT_EQ(7 * 6, 42);
}

TEST(PremiersTestMain, AssertionBasiquesNonEgale) {
  EXPECT_STRNE("Google", "Test");
  EXPECT_NE(1,2);
  EXPECT_NE(7 * 6, 37);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}