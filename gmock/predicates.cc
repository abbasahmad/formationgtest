#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
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


//COMPLETER, EXECUTER

//-----------------------------------------------------------------------------
// Fonction qui retourne vrai si l'entrée est un nombre positif
bool IsPositive(int x) {
    return x > 0;
}

//-----------------------------------------------------------------------------
// Test de la fonction IsPositive avec différentes approches
TEST(ExpectPredTest, IsPositive) {

    // Vérifier que 10 est positif avec EXPECT_TRUE
    //...

    // Vérifier avec EXPECT_PRED1
    //...

}

//-----------------------------------------------------------------------------
// Test de IsPositive avec Truly()
TEST(ExpectPredTest, IsPositiveTruly) {
    EXPECT_THAT(10, Truly(IsPositive));  // Vérifie que 10 est positif avec EXPECT_THAT et Truly()
}


//-----------------------------------------------------------------------------
// Test sans utilisation du matcher Truly()
TEST(MatchersTest, WithoutTruly) {
    std::vector<double> v = { 4, 6, 8, 2 };

    // Vérifier chaque élément du vecteur avec EXPECT_TRUE et EXPECT_PRED1
    //Boucle for ?
    //...
}

//-----------------------------------------------------------------------------
// Test avec le matcher Truly() qui applique une fonction personnalisée
TEST(MatchersTest, WithTruly) {
    std::vector<double> v = { 4, 6, 8, 2 };

    // Utiliser EXPECT_THAT avec des matchers pour vérifier que chaque élément est positif
    
}

