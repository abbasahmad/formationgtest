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
using ::testing::Gt;
using ::testing::HasSubstr;
using ::testing::IsSubsetOf;
using ::testing::Lt;
using ::testing::MatchesRegex;
using ::testing::Ne;
using ::testing::Not;
using ::testing::Pair;
using ::testing::StartsWith;
using ::testing::StrCaseEq;
using ::testing::StrCaseNe;
using ::testing::StrEq;
using ::testing::StrNe;
using ::testing::Truly;
using ::testing::UnorderedElementsAre;
using ::testing::UnorderedElementsAreArray;
using ::testing::WhenSorted;


//Executer, corriger et completer !

//-----------------------------------------------------------------------------
// Test des matchers appliqués aux chaînes de caractères
TEST(MatchersTest, StringMatchers) {
    auto str1 = std::string("This is aa test. Davey.");
    auto str2 = std::string("This is bb test. Bickford.");

    // Vérifie si la chaîne contient un motif spécifique en utilisant des expressions régulières
    EXPECT_THAT(str1, ContainsRegex(".*aa test\\."));   // Vérifie que 'aa test.' apparaît quelque part
    EXPECT_THAT(str1, ContainsRegex("[a]+ test\\."));   // Vérifie que 'a' apparaît au moins une fois avant 'test.'
    EXPECT_THAT(str1, ContainsRegex("a{2} test\\."));   // Vérifie la présence exacte de 'aa test.'
    EXPECT_THAT(str1, ContainsRegex("a{1,} test\\."));  // Vérifie que 'a' apparaît au moins une fois avant 'test.'

    // Vérifie la présence de 'aa test.' ou 'bb test.' dans la chaîne
    EXPECT_THAT(str1, ContainsRegex("(aa|bb) test\\."));
    EXPECT_THAT(str2, ContainsRegex("(aa|bb) test\\."));

    // Vérifie si la chaîne correspond entièrement à un motif regex
    EXPECT_THAT(str1, MatchesRegex("T.*\\."));  // Doit commencer par 'T' et se terminer par un '.'

    // Vérifie si la chaîne commence ou se termine par un sous-texte donné
    EXPECT_THAT(str1, EndsWith("Davey!"));  // Vérifie que str1 se termine par "Davey."
    EXPECT_THAT(str1, StartsWith(" This is"));  // Vérifie que str1 commence par "This is"

    // Vérifie si un sous-texte est contenu dans la chaîne
    EXPECT_THAT(str2, HasSubstr("Bickford"));  // Vérifie que "Bickford" est dans str2
}

//-----------------------------------------------------------------------------
// Test de comparaison entre chaînes de caractères
TEST(MatchersTest, StringEquivalence) {
    auto str1 = std::string("aaaa");
    auto str2 = std::string("AAAA");
    auto str3 = std::string("ccccdddd");

    // Comparaison d'égalité stricte

    // Vérifier que str1 est exactement égal à lui-même
    //...
    // Vérifier que str1 est égal à str1 avec Eq()
    //...
    // Vérifier que str1 est égal à str1 sans matcher explicite
    //...

    // Comparaison d'inégalité stricte

    // Vérifier que str1 est différent de str2
    //...
    // Vérifier que str1 est différent de str2 avec Ne()
    //...
    // Vérifier que str1 n'est pas égal à str2 avec Not()
    //...
    // Vérifier que str1 n'est pas égal à str2 sans matcher explicite
    //...

    // Comparaison insensible à la casse

    // Vérifier que str1 est égal à str2 sans tenir compte de la casse
    //...
    // Vérifier que str1 est différent de str3 même en ignorant la casse
    //...
}
