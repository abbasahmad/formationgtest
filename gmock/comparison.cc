#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::A;
using ::testing::An;
using ::testing::AnyOf;
using ::testing::ContainerEq;
using ::testing::Contains;
using ::testing::ContainsRegex;
using ::testing::Each;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
using ::testing::EndsWith;
using ::testing::Eq;
using ::testing::FieldsAre;
using ::testing::Ge;
using ::testing::Gt;
using ::testing::HasSubstr;
using ::testing::IsFalse;
using ::testing::IsNull;
using ::testing::IsSubsetOf;
using ::testing::IsTrue;
using ::testing::Le;
using ::testing::Lt;
using ::testing::MatchesRegex;
using ::testing::Ne;
using ::testing::Not;
using ::testing::NotNull;
using ::testing::Pair;
using ::testing::Ref;
using ::testing::StartsWith;
using ::testing::StrCaseEq;
using ::testing::StrCaseNe;
using ::testing::StrEq;
using ::testing::StrNe;
using ::testing::Truly;
using ::testing::TypedEq;
using ::testing::UnorderedElementsAre;
using ::testing::UnorderedElementsAreArray;



//EXECUTER LES TEST Et corriger ceux qui ne passent pas

//-----------------------------------------------------------------------------
// Test de comparaisons génériques sur des valeurs entières
TEST(GenericComparison, SimpleComparison) {
  int a = -1;

  EXPECT_THAT(a, Eq(1));   // Vérifie que a est égal à 1
  EXPECT_THAT(a, 1);       // Vérifie directement la valeur de a

  EXPECT_THAT(a, Ge(0));   // Vérifie que a est supérieur ou égal à 0
  EXPECT_THAT(a, Gt(0));   // Vérifie que a est strictement supérieur à 0
  EXPECT_THAT(a, Lt(2));   // Vérifie que a est strictement inférieur à 2
  EXPECT_THAT(a, Le(2));   // Vérifie que a est inférieur ou égal à 2
  EXPECT_THAT(a, Ne(2));   // Vérifie que a est différent de 2
}

//-----------------------------------------------------------------------------
// Test de comparaisons sur des valeurs booléennes
TEST(GenericComparison, BooleanComparison) {
  int boolean_true = true;
  int boolean_false = false;

  EXPECT_THAT(boolean_true, IsFalse());  // Vérifie que la valeur est vraie
  EXPECT_THAT(boolean_false, IsFalse()); // Vérifie que la valeur est fausse
}

//-----------------------------------------------------------------------------
// Test de comparaisons sur les pointeurs
TEST(GenericComparison, PointerComparison) {
  int* ptr_null = nullptr;
  int* ptr_valid = new int(1);

  EXPECT_THAT(ptr_null, IsNull());   // Vérifie que le pointeur est nul
  EXPECT_THAT(ptr_valid, IsNull()); // Vérifie que le pointeur est non nul
  EXPECT_THAT(ptr_valid, Not(IsNull())); // Vérifie que le pointeur est non nul

  delete ptr_valid; // Nettoyage de la mémoire
}

//-----------------------------------------------------------------------------
// Test de référence et d'égalité d'adresses mémoire
TEST(ReferenceTest, SimpleTest) {
  int a = 1;
  int& a_ref = a;
  int b = 1;

  EXPECT_THAT(a_ref, Ref(a));  // Vérifie que a_ref fait bien référence à a
  EXPECT_THAT(b, Ref(a)); // Vérifie que b n'est pas une référence à a
}

//-----------------------------------------------------------------------------
// Test de vérification du type avec TypedEq
TEST(TypedEqTest, SimpleTest) {
  char char_a = 'a';
  int int_a = 'a';

  EXPECT_THAT(char_a, TypedEq<char>('a'));   // Vérifie que char_a est bien un char avec la valeur 'a'
  EXPECT_THAT(char_a, TypedEq<char>('b')); // Vérifie que char_a n'est pas 'b'

  EXPECT_THAT(int_a, TypedEq<int>('a')); // Vérifie que int_a est bien un int et vaut 'a'
  
  // Ne compile pas :
  // EXPECT_THAT(int_a, TypedEq<char>('a')); // Vérification incorrecte du type
}

//-----------------------------------------------------------------------------
// Test d'utilisation du wildcard '_', qui accepte n'importe quelle valeur
TEST(Wildcard, Underscore) {
  int a = 1;
  std::string str_a = "aa";

  EXPECT_THAT(a, 1); // Vérifie que a est égal à 1
  EXPECT_THAT(a, _); // Accepte n'importe quelle valeur
  EXPECT_THAT(str_a, _); // Accepte n'importe quelle chaîne de caractères
}

//-----------------------------------------------------------------------------
// Test d'utilisation de la correspondance sur n'importe quel type avec A<> et An<>
TEST(Wildcard, AnyType) {
  int a = 1;
  auto b = a;

  EXPECT_THAT(a, A<int>());  // Vérifie que a est un entier
  EXPECT_THAT(b, An<int>()); // Vérifie que b est un entier
  // Ne compile pas :
  // EXPECT_THAT(a, An<char>()); // Vérification incorrecte du type
}
