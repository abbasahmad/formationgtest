#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AnyOf;
using ::testing::AllOf;
using ::testing::ContainerEq;
using ::testing::Contains;
using ::testing::Each;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
using ::testing::Eq;
using ::testing::FieldsAre;
using ::testing::Gt;
using ::testing::Field;
using ::testing::Ge;
using ::testing::HasSubstr;
using ::testing::IsSubsetOf;
using ::testing::Key;
using ::testing::Lt;
using ::testing::Matcher;
using ::testing::Not;
using ::testing::Pair;
using ::testing::Pointwise;
using ::testing::PrintToString;
using ::testing::Property;
using ::testing::Truly;
using ::testing::UnorderedElementsAre;
using ::testing::UnorderedElementsAreArray;
using ::testing::WhenSorted;

//Executer et corriger les test afin qu'ils passent! 
//-----------------------------------------------------------------------------
// Test des matchers appliqués aux membres d'une std::map
TEST(MatchersTest, MemberMatchers) {
  std::map<int, int> m = { {1, 100}, {2, 200}, {3, 300} };

  // Vérifie que chaque paire (clé, valeur) a une clé > 0 et une valeur > 99
  EXPECT_THAT(m, Each(Pair(Gt(0), Gt(99))));

  // Vérifie que chaque clé est strictement supérieure à 0
  EXPECT_THAT(m, Each(Key(Gt(0))));

  // Vérifie que chaque valeur est strictement supérieure à 99
  //Utilisation du Wildcard "_" pour la clé
  EXPECT_THAT(m, Each(Pair(_, Gt(99))));

  // Vérifie que chaque clé est > 0 et que chaque valeur est soit > 100, soit égale à 100
  EXPECT_THAT(m, Each(FieldsAre(Gt(0), AnyOf(Lt(100), Eq(100)))));
}

//-----------------------------------------------------------------------------
// Test des matchers appliqués aux éléments d'un tuple
TEST(MatchersTest, MemberMatchersFieldTuple) {
  std::tuple<int, std::string> my_tuple{ 7, "hello world" };

  // Vérifie que le premier élément du tuple est >= 0 ou == 42 et que le second contient "hello"
  EXPECT_THAT(my_tuple, FieldsAre(AllOf(Ge(0), Eq(42)), HasSubstr("hello")));
}

//-----------------------------------------------------------------------------
// Test des matchers appliqués aux membres d'une structure (C++17 requis)
TEST(MatchersTest, MemberMatchersFieldStruct) {
  struct MyStruct {
    int value = 42;
    std::string greeting = "Davey";
  };

  MyStruct s;

  // Vérifie que les champs de la structure correspondent aux valeurs attendues
  EXPECT_THAT(s, FieldsAre(42, "Bickford"));
}

//-----------------------------------------------------------------------------
// Définition d'une classe utilisateur pour tester Field()
class MyClass1 {
public:
  MyClass1(int m) : m_(m) {}

  int m_;
};

// Test du matcher Field() sur un objet simple
TEST(MatchersTest, MemberMatchersFieldSimple) {
  MyClass1 my_object(1);

  // Vérifie que le champ 'm_' de l'objet est >= 0
  EXPECT_THAT(my_object, Field(&MyClass1::m_, Ge(10)));
  EXPECT_THAT(my_object.m_, Ge(0));
}

// Test du matcher Field() appliqué à un conteneur de MyClass1
TEST(MatchersTest, MemberMatchersFieldContainer) {
  std::vector<MyClass1> my_objects = { MyClass1(1), MyClass1(2), MyClass1(3) };

  // Vérifie que chaque objet a un champ 'm_' >= 0
  EXPECT_THAT(my_objects, Each(Field(&MyClass1::m_, Ge(0))));

  // Vérifie que le conteneur contient exactement ces objets dans un ordre quelconque
  EXPECT_THAT(my_objects, UnorderedElementsAre(
    Field(&MyClass1::m_, 1),
    Field(&MyClass1::m_, 3),
    Field(&MyClass1::m_, 2)));
}


//-----------------------------------------------------------------------------
// Définition d'une classe utilisateur pour tester Property()
class MyClass2 {
public:
  MyClass2(int m) : m_(m) {}

  int GetM() const { return m_; }
  void SetM(int new_m) { m_ = new_m; }

private:
  int m_;
};

// Test du matcher Property() sur un objet simple
TEST(MatchersTest, MemberMatchersPropertySimple) {
  MyClass2 my_object(1);

  // Vérifie que la méthode GetM() retourne une valeur >= 0
  //ATTENTION ==> Sela fonctionnen UNIQUEMENT si la fonction n'as pas de parametre et qu'elle est declarer comme "const"
  EXPECT_THAT(my_object, Property(&MyClass2::GetM, Ge(0)));
  EXPECT_THAT(my_object.GetM(), Ge(0));
}

// Test du matcher Property() appliqué à un conteneur de MyClass2
TEST(MatchersTest, MemberMatchersPropertyContainer) {
  std::vector<MyClass2> my_objects = { MyClass2(1), MyClass2(2), MyClass2(3) };

  // Vérifie que chaque objet a une valeur retournée par GetM() >= 0
  EXPECT_THAT(my_objects, Each(Property(&MyClass2::GetM, Ge(0))));

  // Vérifie que le conteneur contient exactement ces objets dans un ordre quelconque
  EXPECT_THAT(my_objects, UnorderedElementsAre(
    Property(&MyClass2::GetM, 1),
    Property(&MyClass2::GetM, 3),
    Property(&MyClass2::GetM, 2)));
}
