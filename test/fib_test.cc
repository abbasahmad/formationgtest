#include "gtest/gtest.h"


int Fib(int n) {
  if (n <= 1) {
    return n;
  }
  return Fib(n - 1) + Fib(n - 2);
}


//Ajouter des test pour des valeurs non negatives



//Ajouter des test pour les 5 premier nombre de la suite de fibonnaci