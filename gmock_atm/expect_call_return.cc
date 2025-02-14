#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

// Importation des fonctionnalités de Google Mock pour simplifier l'écriture des tests
using ::testing::_;
using ::testing::DoDefault;
using ::testing::Gt;
using ::testing::Return;
using ::testing::ReturnArg;
using ::testing::ReturnPointee;
using ::testing::ReturnRef;
using ::testing::ReturnRoundRobin;
using ::testing::NiceMock;

//-----------------------------------------------------------------------------
// Classe Mock qui simule le comportement du serveur bancaire.
// Elle permet de tester le distributeur automatique (ATM) sans dépendre d'un serveur réel.
class MockBankServer : public BankServer {
 public:
  MOCK_METHOD(void, Connect, (), (override));  // Simule la connexion au serveur bancaire
  MOCK_METHOD(void, Disconnect, (), (override));  // Simule la déconnexion
  MOCK_METHOD(void, Credit, (int, int), (override));  // Simule un crédit sur un compte
  MOCK_METHOD(void, Debit, (int, int), (override));  // Simule un débit sur un compte
  MOCK_METHOD(bool, DoubleTransaction, (int, int, int), (override));  // Vérifie une double transaction
  MOCK_METHOD(int, GetBalance, (int), (const, override));  // Récupère le solde du compte
};

//-----------------------------------------------------------------------------
// Teste si l'ATM peut effectuer un retrait en utilisant la fonction ReturnRoundRobin
// Cette fonction permet de retourner des valeurs différentes à chaque appel successif.
TEST(AtmMachine, CanWithdrawReturnRoundRobin) {
  // Arrange : Définition des variables de test
  const int account_number = 1234;
  const int withdraw_value = 1000;

  NiceMock<MockBankServer> mock_bankserver;

  // Expectations : Simulation du comportement du serveur
  // La première fois, GetBalance retourne 2000, puis 3000, puis 4000.
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
      .Times(3)
      .WillRepeatedly(ReturnRoundRobin({2000, 3000, 4000}));

  // Act : Création de l'ATM et simulation de plusieurs retraits
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = true;
  for (int i = 0; i < 3; i++) {
    withdraw_result =
        withdraw_result && atm_machine.Withdraw(account_number, withdraw_value);
  }

  // Assert : Vérification que tous les retraits ont réussi
  EXPECT_TRUE(withdraw_result);
}

//-----------------------------------------------------------------------------
// Teste le retrait en utilisant ReturnArg
// Cette fonction retourne la valeur du premier argument de la fonction GetBalance.
TEST(AtmMachine, CanWithdrawReturnArg) {
  // Arrange
  const int account_number = 1234;
  const int withdraw_value = 1000;

  NiceMock<MockBankServer> mock_bankserver;

  // Expectations : GetBalance retourne toujours le numéro de compte en guise de solde
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
      .Times(3)
      .WillRepeatedly(ReturnArg<0>());  // Retourne le premier argument (numéro du compte)

  // Act : Essai de retraits successifs
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = true;
  for (int i = 0; i < 3; i++) {
    withdraw_result =
        withdraw_result && atm_machine.Withdraw(account_number, withdraw_value);
  }

  // Assert : Vérification que les retraits ont bien fonctionné
  EXPECT_TRUE(withdraw_result);
}

//-----------------------------------------------------------------------------
// Teste différents comportements de retour dans un même test
// - ReturnPointee : Retourne la valeur pointée par un pointeur
// - ReturnArg : Retourne le premier argument reçu
// - Return : Retourne une valeur fixe

TEST(AtmMachine, CanWithdrawReturnMultiple) {
  // Arrange
  const int account_number = 1234;
  const int withdraw_value = 1000;
  int current_balance = 10000;  // Solde initial
  int* ptr = &current_balance;  // Pointeur vers le solde

  NiceMock<MockBankServer> mock_bankserver;

  // Expectations : Définition du comportement simulé du serveur
  EXPECT_CALL(mock_bankserver, Connect()).WillRepeatedly(Return());

  // GetBalance retourne différentes valeurs :
  // - Une fois : retourne la valeur pointée par ptr (current_balance = 10000)
  // - Une fois : retourne le premier argument reçu (numéro du compte)
  // - Puis : retourne toujours la valeur actuelle de current_balance
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
      .WillOnce(ReturnPointee(ptr))  // Retourne la valeur actuelle de current_balance
      .WillOnce(ReturnArg<0>())  // Retourne le numéro du compte (1234)
      .WillRepeatedly(Return(current_balance));  // Retourne toujours 10000 après

  // Simulation de la déconnexion, qui exécute l'action par défaut
  EXPECT_CALL(mock_bankserver, Disconnect()).WillRepeatedly(DoDefault());

  // Act : Effectuer plusieurs retraits
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = true;
  for (int i = 0; i < 10; i++) {
    withdraw_result =
        withdraw_result && atm_machine.Withdraw(account_number, withdraw_value);
  }

  // Assert : Vérification que les retraits ont réussi
  EXPECT_TRUE(withdraw_result);
}
