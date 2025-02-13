#include "gtest/gtest.h"

class DivideByZero : public virtual std::exception {
  // what est une fonction virtuelle qui renvoie une description
    public:
        const char* what() const noexcept override { return "Divide By Zero Error!"; }
};

//Creer des test pour les EXPECT_THROW ASSERT_TROW et les *_NO_THROW

int Divide(int a, int b) {
    if (b == 0) {
        throw DivideByZero();
    }
    return a / b;
}
  
TEST(DivideTest, SimpleDivision) {
    EXPECT_EQ(Divide(6, 2), 3);
    EXPECT_EQ(Divide(2, 2), 1);
}




//ENSEMBLE Comment tester le message de l'exception ?
