#include "gtest/gtest.h"

TEST(AssertAndExpect, AssertFailIsFatal) {
  ASSERT_TRUE(false);
  std::cout << "Cette ligne ne seras pas executé !" << std::endl;
  EXPECT_TRUE(false);
}

TEST(AssertAndExpect, ExpectFailIsNotFatal) {
  EXPECT_TRUE(false);
  std::cout << "Cette ligne seras executé ! " << std::endl;
  EXPECT_TRUE(false);
}