#include <regex>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AllOf;
using ::testing::Gt;
using ::testing::Lt;
using ::testing::MatchesRegex;
using ::testing::StartsWith;
using ::testing::Value;
using ::testing::IsTrue;
using ::testing::Matcher;


// Test d'égalité avec EXPECT_EQ
//Le mode classique que l'on a vu
TEST(MatchersTest, ExpectEq) {
    EXPECT_EQ(1, 1);         // Vérifie que 1 est égal à 1
    EXPECT_EQ(0, 2 - 2);     // Vérifie que 0 est bien le résultat de 2 - 2
    EXPECT_TRUE(1 == 1);     // Vérifie une condition booléenne simple
}

// Test basique d'EXPECT_THAT avec des valeurs simples
//A EVITER
TEST(MatchersTest, ExpectThat) {
    EXPECT_THAT(1, 1);         // Vérifie que 1 est bien égal à 1
    EXPECT_THAT(2 - 2, 0);     // Vérifie que 2 - 2 donne bien 0
    EXPECT_THAT(1 == 1, true); // Vérifie que l'expression booléenne est vraie
}

//-----------------------------------------------------------------------------
// Test d'utilisation de matchers simples avec EXPECT_TRUE
TEST(MatchersTest, SimpleMatcher) {
    Matcher<int> is_one = 1;
    Matcher<int> is_zero = 0;
    Matcher<bool> is_true = true;

    EXPECT_TRUE(is_one.Matches(1));       // Vérifie que 1 correspond au matcher is_one
    EXPECT_TRUE(is_zero.Matches(2 - 2));  // Vérifie que 0 correspond au matcher is_zero
    EXPECT_TRUE(is_true.Matches(1 == 1)); // Vérifie que true correspond au matcher is_true

    EXPECT_TRUE(Matches(is_one)(1));  // Vérifie l'égalité via Matches()
    EXPECT_TRUE(Matches(is_zero)(0));
    EXPECT_TRUE(Matches(is_true)(true));
}

// Test d'utilisation de matchers simples avec EXPECT_THAT
TEST(MatchersTest, SimpleMatcherExpectThat) {
    Matcher<int> is_one = 1;
    Matcher<int> is_zero = 0;
    Matcher<bool> is_true = true;

    //UTILISER EXPECT_THAT pour: 
    // Vérifier que 1 correspond au matcher is_one
    // Vérifier que 0 correspond au matcher is_zero
    // Vérifier que true correspond au matcher is_true
    //...
}


//-----------------------------------------------------------------------------
// Test sans utilisation explicite des matchers Google Test
TEST(MatchersTest, NoMatcherIsUSed) {
    std::string test_string("Hello, this is a test string. We are here to help!");

    EXPECT_TRUE(test_string.rfind("Hello", 0) == 0); // Vérifie que la chaîne commence par "Hello" avec rfind de std::string
    EXPECT_TRUE(std::regex_match(test_string, std::regex(".*is.*help.*"))); // Vérifie une correspondance regex

    EXPECT_GT(10, 0);   // Vérifie que 10 est supérieur à 0 avec google test
    EXPECT_LT(10, 100); // Vérifie que 10 est inférieur à 100 avec google test

    //On veut eviter d'ecrire du code dans nos test sinon il nous faudrais des test pour nos test! 
}

// CREER un test "MatchersAreUsedWithExpectThat" pour faire le meme test que le précedent en tilisant les matchers StartsWith, MatchRegex, AllOf(), Gt(), Lt() en combinaison avec EXPECT_THAT
//...


// Faite le meme Test avec matchers assignés à des variables m1 m2 m3
//...
