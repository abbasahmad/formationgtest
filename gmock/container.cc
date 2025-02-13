#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <list>

using ::testing::_;
using ::testing::AnyOf;
using ::testing::ContainerEq;
using ::testing::Contains;
using ::testing::Each;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
using ::testing::Eq;
using ::testing::FieldsAre;
using ::testing::Ge;
using ::testing::Gt;
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
using ::testing::WhenSortedBy;

//-----------------------------------------------------------------------------
// Vérifie si un vecteur contient exactement les éléments donnés, dans le même ordre
TEST(MatchersTest, ElementsAre) {
  std::vector<int> v = {3, 4, 5, 2, 6, 7, 8, 9, 10};

  EXPECT_THAT(v, ElementsAre(3, 4, 5, 2, 6, 7, 8, 9, 10));
}

//-----------------------------------------------------------------------------
// Vérifie si un vecteur est correctement trié avant la comparaison
TEST(MatchersTest, WhenSorted) {
  std::vector<int> v = {3, 4, 5, 2, 6, 7, 8, 9, 10};

  // Vérifie si le vecteur, une fois trié, correspond exactement aux valeurs données
  EXPECT_THAT(v, WhenSorted(ElementsAre(2, 3, 4, 5, 6, 7, 8, 9, 10)));

  // Vérifie si le vecteur, une fois trié en ordre décroissant, correspond aux valeurs attendues
  EXPECT_THAT(v, WhenSortedBy(std::greater<int>(), ElementsAre(10, 9, 8, 7, 6, 5, 4, 3, 2)));
}

//-----------------------------------------------------------------------------
// Vérifie si un vecteur contient les mêmes éléments, indépendamment de l'ordre
TEST(MatchersTest, UnorderedElementsAre) {
  std::vector<int> v = {3, 4, 5, 2};

  EXPECT_THAT(v, UnorderedElementsAre(4, 3, 5, 2)); // L'ordre n'a pas d'importance
}

//-----------------------------------------------------------------------------
// Vérifie si un vecteur contient les mêmes éléments qu'un autre tableau, indépendamment de l'ordre
TEST(MatchersTest, UnorderedElementsAreArray) {
  std::vector<int> v = {3, 4, 5, 2, 6, 7, 8, 9, 10};

  EXPECT_THAT(v, UnorderedElementsAreArray({2, 3, 4, 5, 6, 7, 8, 9, 10}));
  EXPECT_THAT(v, UnorderedElementsAreArray(v.begin(), v.end()));
}

//-----------------------------------------------------------------------------
// Vérifie si un vecteur contient les mêmes éléments qu'un set, indépendamment de l'ordre
TEST(MatchersTest, UnorderedElementsAreArray_Set) {
  std::vector<int> v = {3, 4, 5, 2, 6, 7, 8, 9, 10};
  std::set<int> s(v.begin(), v.end());

  EXPECT_THAT(v, UnorderedElementsAreArray(s.begin(), s.end()));
}

//-----------------------------------------------------------------------------
// Vérifie des propriétés générales sur un conteneur
TEST(MatchersTest, ContainerMatchers) {
  std::vector<int> v = {4, 6, 8, 2, 2};
  std::vector<int> u = {4, 6};

  EXPECT_THAT(v, Each(Gt(1)));  // Vérifie que chaque élément est supérieur à 1

  EXPECT_THAT(v, Contains(6));  // Vérifie que 6 est présent dans le vecteur

  EXPECT_THAT(u, IsSubsetOf(v));  // Vérifie que tous les éléments de u sont dans v

  EXPECT_THAT(v, Contains(Gt(1)));  // Vérifie qu'au moins un élément est supérieur à 1

  // Vérifie que chaque élément est soit supérieur à 2, soit supérieur à 0
  EXPECT_THAT(v, Each(AnyOf(Gt(2), Gt(0))));
}

//-----------------------------------------------------------------------------
// Vérifie le nombre d'occurrences d'un élément dans un conteneur
TEST(MatchersTest, ContainerMatchers_ContainsNTimes) {
  std::vector<int> v = {4, 6, 8, 2, 2, 3, 3, 3, 4};

  EXPECT_THAT(v, Contains(3).Times(3));  // Vérifie que 3 apparaît exactement 3 fois
  EXPECT_THAT(v, Contains(4).Times(2));  // Vérifie que 4 apparaît exactement 2 fois
  EXPECT_THAT(v, Contains(1).Times(0));  // Vérifie que 1 n'apparaît pas
}

//-----------------------------------------------------------------------------
// Vérifie si les éléments de deux conteneurs sont en relation selon un critère donné
TEST(MatchersTest, ContainerMatchers_Pointwise) {
  //lhs → Left-Hand Side (Côté gauche)
  //rhs → Right-Hand Side (Côté droit)
  std::list<int> lhs{1, 2, 3};
  std::vector<int> rhs{4, 5, 6};

  EXPECT_THAT(lhs, Pointwise(Lt(), rhs)); // Vérifie que chaque élément de lhs est < à l'élément correspondant de rhs
  EXPECT_THAT(lhs, Not(Pointwise(Gt(), rhs))); // Vérifie que lhs n'a pas d'éléments > à rhs
}

//-----------------------------------------------------------------------------
// Vérifie si deux conteneurs sont exactement égaux
TEST(MatchersTest, ContainerMatchers_ContainerEq) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  std::vector<int> v2{1, 2, 3};

  EXPECT_THAT(v1, Not(v2)); // Vérifie que v1 n'est pas égal à v2
  EXPECT_THAT(v1, Not(ContainerEq(v2))); // Vérifie que v1 n'est pas strictement égal à v2
}
