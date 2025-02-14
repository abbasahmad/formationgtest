#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AllOf;
using ::testing::AnyOf;
using ::testing::ContainerEq;
using ::testing::Contains;
using ::testing::Each;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
using ::testing::Eq;
using ::testing::FieldsAre;
using ::testing::Gt;
using ::testing::Ge;
using ::testing::HasSubstr;
using ::testing::IsSubsetOf;
using ::testing::Lt;
using ::testing::Matcher;
using ::testing::Not;
using ::testing::Pair;
using ::testing::Pointwise;
using ::testing::PrintToString;
using ::testing::Truly;
using ::testing::UnorderedElementsAre;
using ::testing::UnorderedElementsAreArray;
using ::testing::WhenSorted;

//-----------------------------------------------------------------------------
// Définition de matchers personnalisés
/*
 * Il doit retourner un booléen.
 * La valeur en cours de correspondance peut être référencée par "arg"
 * et son type peut être référencé par "arg_type".
 *
 * La chaîne de description : génère le message d’échec.
 *   - Elle peut (et devrait) faire référence à la variable booléenne spéciale "negation".
 *
 * Facultativement, vous pouvez transmettre des informations supplémentaires
 * à un pointeur caché nommé "result_listener" pour expliquer le résultat de la correspondance.
 */


 //COMPLETER, EXECUTER --> Regarder comment le google mock vous ecrit les fail en sortie avec le nom des fonctions en Camel Case

 //-----------------------------------------------------------------------------

 // Vérifie si un nombre est pair
MATCHER(IsEven, "") { return (arg % 2) == 0; }

// Même matcher avec une notation en camel case (juste pour démonstration)
MATCHER(IsEvenBtwIUnderstandCamelNotation, "") { return (arg % 2) == 0; }

// Vérifie si un nombre est impair
MATCHER(IsOdd, "") { return (arg % 2) != 0; }

// Vérifie si un nombre est divisible par un autre
MATCHER_P(IsDivisibleBy, n, "") {
  *result_listener << "where the remainder is " << (arg % n);
  return (arg % n) == 0;
}

// Vérifie si un nombre est compris entre deux bornes [a, b]
MATCHER_P2(IsBetween, a, b,
  (std::string(negation ? "Isn't" : "Is") + " between " +
    PrintToString(a) + " and " + PrintToString(b))) {
  return a <= arg && arg <= b;
}

// Vérifie si un nombre correspond à l'une des trois valeurs données
MATCHER_P3(IsOneOf, a, b, c, "") {
  return arg == a || arg == b || arg == c;
}


//-----------------------------------------------------------------------------
// Tests unitaires des matchers personnalisés
//-----------------------------------------------------------------------------

// Test du matcher IsEven()
TEST(MatchersTest, CustomMatchers) {
  // Vérifier que 10 est pair
  //...
  // Vérifier que 9 n'est pas pair
  //...

}

// Test du matcher IsEven() avec une notation en camel case
TEST(MatchersTest, CustomMatchersCamel) {
   // Vérifier que 8 est pair
   //...
   // Vérifier que 9 n'est pas pair
   //...
}

// Test du matcher IsBetween() pour vérifier l'inclusion dans un intervalle
TEST(MatchersTest, CustomMatchersWithDescription) {

  // Vérifie que 10 est dans [9, 11]
  //...

  // Vérifie que 100 n'est pas dans [9, 11]
  //...

}

// Test du matcher IsDivisibleBy()
TEST(MatchersTest, CustomMatchersExtraDescription) {
  // Vérifie que 10 est divisible par 2
  //...

  // Vérifie que 9 n'est pas divisible par 2
  //...

  // Vérifier que tous les éléments du vecteur sont divisibles par 2
  std::vector<int> v = { 4, 6, 8, 2 };
  //...
}

// Test combiné de plusieurs matchers personnalisés
TEST(MatchersTest, CustomMatchersComposite) {
  std::vector<int> v = { 4, 6, 8, 2 };

  // Vérifie que chaque élément du vecteur est divisible par 2
  //...

  // Vérifier plusieurs conditions pour chaque élément du vecteur
  //...
    // Inférieur à 5
    // Nombre pair
    // Compris entre 1 et 10
    // Pas compris entre 5 et 10


  // Vérifier que chaque élément n'est pas dans l'intervalle [-1, -2]
  //...
}

// Test du matcher IsOneOf() avec trois paramètres
TEST(MatchersTest, CustomMatchersThreeParameters) {
  // Vérifier que 4 est l'une des valeurs attendues
  //...
}
