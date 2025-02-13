#include "gtest/gtest.h"


TEST(BasicChecks, EnabledTest) {
    EXPECT_TRUE(true);
    EXPECT_TRUE(true);
}

//Ajouter DISABLED_ au nom du test pour le désactiver
TEST(BasicChecks, SomeBrokenTest) {
    EXPECT_TRUE(false);
    EXPECT_TRUE(false);
}


class DISABLED_BasicChecks : public testing::Test {};
TEST_F(DISABLED_BasicChecks, SomeTest1) {
    EXPECT_TRUE(false);
}
TEST_F(DISABLED_BasicChecks, SomeTest2) {
    EXPECT_TRUE(false);
}


//Skip un test : Exemple
//Aller sur le fichier "fixture_test.cc" et skipper tout les tests avec une ligne de code seulement
TEST(BasicChecks, EnabledButSkippedTest) {
    GTEST_SKIP() << "Skipping single test";
    EXPECT_TRUE(false);
    EXPECT_TRUE(false);
}


