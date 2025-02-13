#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AllOf;
using ::testing::AllOfArray;
using ::testing::AnyOf;
using ::testing::Conditional;
using ::testing::ContainerEq;
using ::testing::Contains;
using ::testing::ContainsRegex;
using ::testing::Each;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
using ::testing::EndsWith;
using ::testing::Eq;
using ::testing::FieldsAre;
using ::testing::Gt;
using ::testing::HasSubstr;
using ::testing::IsSubsetOf;
using ::testing::Lt;
using ::testing::Matcher;
using ::testing::MatchesRegex;
using ::testing::Not;
using ::testing::Pair;
using ::testing::StartsWith;
using ::testing::Truly;
using ::testing::UnorderedElementsAre;
using ::testing::UnorderedElementsAreArray;
using ::testing::WhenSorted;


//Executer, corriger, completer! 

//-----------------------------------------------------------------------------
// Test des matchers composites avec des entiers
TEST(MatchersTest, CompositMatchersSimple) {
    int a = 1;

    // Vérifie que 'a' est égal à 1, supérieur à 0 et inférieur à 5
    EXPECT_THAT(a, AllOf(Eq(1), Gt(5), Lt(5)));

    // Vérifier que 'a' ne satisfait pas toutes les conditions Eq(1), Lt(0), Gt(5)
    //...

    // Vérifier que 'a' satisfait au moins une des conditions Eq(1), Lt(0), Gt(5)
    //...
}

//-----------------------------------------------------------------------------
// Test des matchers composites appliqués aux chaînes de caractères
TEST(MatchersTest, CompositMatchers) {
    auto str = std::string("This is aa test. Davey.");

    // Vérifie que la chaîne contient "aa" et "test"
    EXPECT_THAT(str, AllOf(HasSubstr("aa"), HasSubstr("test")));

    // Vérifier que la chaîne ne contient pas à la fois "aa" et "bb"
    //...

    // Vérifier que la chaîne contient au moins "aa" ou "bb"
    //...

    // Liste de matchers vérifiant si la chaîne se termine par "Davey."
    // et contient "aa t"
    std::vector<Matcher<std::string>> matchers = { 
        EndsWith("Davey."),
        HasSubstr("aa t") 
    };
    EXPECT_THAT(str, Not(AllOfArray(matchers))); // Applique tous les matchers à la chaîne

    // Test conditionnel basé sur une variable booléenne
    bool selector = true;
    EXPECT_THAT(str, Conditional(selector, HasSubstr("Bickford"), HasSubstr("aa"))); // Si selector est vrai, teste HasSubstr("aa"), sinon teste HasSubstr("bb")
    
}
