#include "gtest/gtest.h"

// Créer plusieurs test pour tester les assertions communes, inspirer vous des exemples

TEST(BasicChecks, FalseAndTrue) {
    int a = 0;
    int b = 1;
    EXPECT_TRUE(a == 0);
    EXPECT_TRUE(b == 1);
    EXPECT_FALSE(a == b);
}

TEST(BasicChecks, SimpleAssertMacros) {
    int a = 0;
    int b = 1;
    ASSERT_EQ(a, a);
    ASSERT_GT(a, b); // This will fail
    //... continuez

    std::cout << ">--------------------After Assert-------------------->" << std::endl;
}



// DEMO : Faire des deffaillances "Manuelement"
TEST(BasicChecks, ExplicitSuccessFails) {
    SUCCEED();      
    ADD_FAILURE();     // Cela entraînera une défaillance non fatale.
    ADD_FAILURE_AT("MyTestFile.cc", 10); // Cela entraînera une défaillance non fatale.
    FAIL(); // Cela entraînera une défaillance  fatale.

    std::cout << ">--------------------After FAIL-------------------->" << std::endl;
  }
  