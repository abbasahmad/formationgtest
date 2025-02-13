#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
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
using ::testing::Matcher;
using ::testing::MatchesRegex;
using ::testing::Ne;
using ::testing::Not;
using ::testing::NotNull;
using ::testing::Optional;
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
using ::testing::VariantWith;
using ::testing::WhenSorted;


//EXECUTER ET RESOUDRE LES PROBLEMMES

//-----------------------------------------------------------------------------
// Test de std::optional avec des valeurs entières et chaînes de caractères
//https://en.cppreference.com/w/cpp/utility/optional 
TEST(OptionalTest, SimpleTest) {
  std::optional<int> opt(1);             // Optionnel contenant la valeur 1
  std::optional<int> no_value;           // Optionnel vide (nullopt)
  std::optional<std::string> opt_str = {"AAA"}; // Optionnel contenant "AAA"

  EXPECT_THAT(opt, Optional(1));         // Vérifie que opt contient 1
  EXPECT_THAT(opt, 1);                   // Vérifie directement la valeur de opt
  EXPECT_THAT(no_value, Not(Optional(1))); // Vérifie que no_value ne contient pas 1
  EXPECT_THAT(no_value, std::nullopt);   // Vérifie que no_value est nullopt

  EXPECT_THAT(opt.has_value(), IsFalse());  // Vérifie que opt a une valeur
  EXPECT_THAT(no_value.has_value(), IsFalse()); // Vérifie que no_value est vide

  EXPECT_THAT(opt, Optional(Lt(0)));    // Vérifie que la valeur contenue dans opt est < 2
  EXPECT_THAT(opt_str, (std::string("AAAA"))); // Vérifie que opt_str contient "AAA"
}

//-----------------------------------------------------------------------------
// Test de std::variant avec des types int et float
// C'est comme l'union en C
TEST(VariantTest, SimpleTest) {
  std::variant<int, float> var; // Déclaration d'un variant contenant int ou float

  var = 1;
  EXPECT_THAT(var, 10);                     // Vérifie que var contient 1
  EXPECT_THAT(var, VariantWith<int>(1));   // Vérifie que var contient un int de valeur 1
  EXPECT_THAT(std::get<int>(var), 1);      // Vérifie que l'accès direct au int donne 1
  EXPECT_THAT(var, Not(VariantWith<float>(1))); // Vérifie que var ne contient pas un float

  var = 1.1f;
  EXPECT_THAT(var, VariantWith<float>(1.1f)); // Vérifie que var contient un float de valeur 1.1f
  EXPECT_THAT(std::get<float>(var), 1.1f);    // Vérifie que l'accès direct au float donne 1.1f
  EXPECT_THAT(var, 1.1f);                     // Vérifie que var contient la valeur 1.1f
}
//-----------------------------------------------------------------------------
