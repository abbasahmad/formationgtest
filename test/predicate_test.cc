#include "gtest/gtest.h"

bool IsAlmostEq(int a, int b) {
  if (std::abs(a - b) < 10)
    return true;
  else
    return false;
}

testing::AssertionResult IsAlmostEq2(int a, int b) {
  if (std::abs(a - b) < 10) {
    return testing::AssertionSuccess();
  }
  else {
    return testing::AssertionFailure()
      << "a is " << a << " and b is: " << b
      << ". The difference is: " << std::abs(a - b);
  }
}

TEST(ExpectPredTest, IsAlmostEq) {
  int a = 10;
  int b = 1000;

  //Soit
  EXPECT_TRUE(IsAlmostEq(a, b));
  //OU
  EXPECT_PRED2(IsAlmostEq, a, b);   //La difference est dans l'output de l'execution : EXPECT_PRED2 donne plus d'informations
}


//Si vous etes pas satisfait, vous pouvez customiser le message avec l'exemple de IsAlmostEq2
//Ici le type de retour est uniquelent "compris" par Google Test et la fonction n'est pas utilisable en dehors de ce cadre
TEST(ExpectPredTest, IsAlmostEq2) {
  int a = 10;
  int b = 1000;
  EXPECT_TRUE(IsAlmostEq2(a, b));
}
