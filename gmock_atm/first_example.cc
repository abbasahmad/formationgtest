#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

//-----------------------------------------------------------------------------
// Classe MockBankServer qui simule le comportement du serveur bancaire
class MockBankServer : public BankServer {
 public:
  // Simulation de la connexion au serveur
  MOCK_METHOD(void, Connect, (), (override));

  // Simulation de la déconnexion du serveur
  MOCK_METHOD(void, Disconnect, (), (override));

  // Simulation d'un crédit sur un compte bancaire
  MOCK_METHOD(void, Credit, (int, int), (override));

  // Simulation d'un débit sur un compte bancaire
  MOCK_METHOD(void, Debit, (int, int), (override));

  // Simulation d'une vérification de double transaction
  MOCK_METHOD(bool, DoubleTransaction, (int, int, int), (override));

  // Simulation de la récupération du solde d'un compte bancaire
  MOCK_METHOD(int, GetBalance, (int), (const, override));
};

// Test de l'ATM : tentative de retrait avec un solde insuffisant
TEST(AtmMachine, OnCallWithZero) {
  
  // Préparation du test
  MockBankServer mock_bankserver;

  // Définition du comportement attendu du mock
  // ON ne specifie rien donc le resultat retournera false

  // Exécution du test
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(/*account_number=*/1234, /*value=*/1000);

  // Vérification du résultat attendu : le retrait doit échouer
  EXPECT_FALSE(withdraw_result);
};