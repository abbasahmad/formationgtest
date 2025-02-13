#include "gtest/gtest.h"

void MyFunction(int n) {
  // verifie si n est pair
  EXPECT_EQ(n, 2);
}


//Regarder les log de tests. Pouvez vous facilement dire pourquoi les tests echouent ?
//Le rapport vous donne juste la ligne d'echec
TEST(SubTest, WithoutScopeTraceSimple) {
  MyFunction(1);
  MyFunction(1);
  MyFunction(1);
}


//SOLUTION : SCOPED_TRACE
TEST(SubTest, WithScopeTrace) {

  SCOPED_TRACE("MyScope1");

  MyFunction(1);

  SCOPED_TRACE("MyScope2");
  MyFunction(1);

  SCOPED_TRACE("MyScope3");
  MyFunction(1);
}



TEST(SubTest, WithNestedScopeTrace) {
  {
    SCOPED_TRACE("MyScope1");
    MyFunction(1);

    {
      SCOPED_TRACE("MyScope2");
      MyFunction(1);
      {

        SCOPED_TRACE("MyScope3");
        MyFunction(1);
      }
    }
  }
}
