#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

//-----------------------------------------------------------------------------
// Importation de Google Mock pour gérer les séquences et checkpoints
using ::testing::InSequence;
using ::testing::MockFunction;

//-----------------------------------------------------------------------------
// Classe Mock simulant un serveur bancaire pour les tests.
class MockBankServer : public BankServer {
public:
  MOCK_METHOD(void, Connect, (), (override));  // Simule la connexion au serveur
  MOCK_METHOD(void, Disconnect, (), (override));  // Simule la déconnexion
  MOCK_METHOD(void, Credit, (int, int), (override));  // Simule un crédit sur un compte
  MOCK_METHOD(void, Debit, (int, int), (override));  // Simule un débit sur un compte
  MOCK_METHOD(bool, DoubleTransaction, (int, int, int), (override));  // Vérifie une double transaction
  MOCK_METHOD(int, GetBalance, (int), (const, override));  // Retourne le solde d'un compte
};

//-----------------------------------------------------------------------------
// Classe servant de checkpoint pour contrôler l'ordre des appels
class Checkpoint {
public:
  MOCK_METHOD(void, Check, (std::string), ());
};

//-----------------------------------------------------------------------------
// Classe de test pour la fonction `Withdraw10kProducts`
class Withdraw10kProductsTest : public ::testing::Test {
public:
  MockBankServer mock_bank_server;

  // Si la valeur est un multiple de 10000, elle effectue un retrait de 10000
  // du compte 1234.
  void Withdraw10kProducts(int value) {
    if (value % 10000 == 0) {
      mock_bank_server.Debit(1234, 10000);
    }
  }
};

//-----------------------------------------------------------------------------
// Test vérifiant que la méthode `Debit` est appelée exactement 2 fois
TEST_F(Withdraw10kProductsTest, WithdrawIsCalledTwice) {
  // Arrange : Définition des attentes
  EXPECT_CALL(mock_bank_server, Debit(1234, 10000)).Times(2);

  // Act : Exécution de la fonction avec différentes valeurs
  Withdraw10kProducts(20000);  // Appel attendu
  Withdraw10kProducts(2000);   // Pas d'appel attendu
  Withdraw10kProducts(3000);   // Pas d'appel attendu
  Withdraw10kProducts(4000);   // Pas d'appel attendu
  Withdraw10kProducts(30000);  // Appel attendu

  // Assert implicite : Les attentes définies par `EXPECT_CALL` doivent être respectées.
}

//-----------------------------------------------------------------------------
// Test vérifiant que les appels à `Debit` respectent un ordre précis grâce aux checkpoints.
TEST_F(Withdraw10kProductsTest, WithdrawIsCalledCorrectlyCheckpoint) {
  Checkpoint checkpoint;

  // Enforce un ordre strict sur les appels avec `InSequence`
  {
    InSequence s;

    EXPECT_CALL(mock_bank_server, Debit(1234, 10000));  // Premier appel
    EXPECT_CALL(checkpoint, Check("1"));               // Checkpoint 1
    EXPECT_CALL(checkpoint, Check("2"));               // Checkpoint 2
    EXPECT_CALL(mock_bank_server, Debit(1234, 10000));  // Deuxième appel
  }

  // Act
  Withdraw10kProducts(20000);  // Premier retrait (déclenche Debit)
  checkpoint.Check("1");        // Vérification du premier checkpoint

  // Aucun retrait ne doit être effectué ici
  Withdraw10kProducts(2000);
  Withdraw10kProducts(3000);
  Withdraw10kProducts(4000);

  // Vérification du second checkpoint
  checkpoint.Check("2");
  Withdraw10kProducts(30000);  // Deuxième retrait (déclenche Debit)

  // Assert implicite : Respect de la séquence attendue.
}

//-----------------------------------------------------------------------------
// Test similaire au précédent, mais utilisant `MockFunction` au lieu d'une classe dédiée.
TEST_F(Withdraw10kProductsTest, WithdrawIsCalledCorrectly) {
  // `MockFunction` permet de créer un mock de fonction pour gérer les checkpoints
  MockFunction<void(std::string check_point_name)> checkpoint;

  // Enforce un ordre strict des appels avec `InSequence`
  {
    InSequence s;

    EXPECT_CALL(mock_bank_server, Debit(1234, 10000));  // Premier appel
    EXPECT_CALL(checkpoint, Call("1"));                // Checkpoint 1
    EXPECT_CALL(checkpoint, Call("2"));                // Checkpoint 2
    EXPECT_CALL(mock_bank_server, Debit(1234, 10000));  // Deuxième appel
  }

  // Act
  Withdraw10kProducts(20000);  // Premier retrait (déclenche Debit)
  checkpoint.Call("1");        // Vérification du premier checkpoint

  // Aucun retrait ne doit être effectué ici
  Withdraw10kProducts(2000);
  Withdraw10kProducts(3000);
  Withdraw10kProducts(4000);

  // Vérification du second checkpoint
  checkpoint.Call("2");
  Withdraw10kProducts(30000);  // Deuxième retrait (déclenche Debit)

  // Assert implicite : Respect de la séquence attendue.
}
