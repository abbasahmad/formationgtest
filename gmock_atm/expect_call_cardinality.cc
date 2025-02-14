#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AtLeast;
using ::testing::AtMost;
using ::testing::Exactly;
using ::testing::Gt;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::ThrowsMessage;

//-----------------------------------------------------------------------------
// Classe simulant un serveur bancaire pour les tests
class MockBankServer : public BankServer {
 public:
  MOCK_METHOD(void, Connect, (), (override));
  MOCK_METHOD(void, Disconnect, (), (override));
  MOCK_METHOD(void, Credit, (int, int), (override));
  MOCK_METHOD(void, Debit, (int, int), (override));
  MOCK_METHOD(bool, DoubleTransaction, (int, int, int), (override));
  MOCK_METHOD(int, GetBalance, (int), (const, override));
};

//-----------------------------------------------------------------------------
// Test : Vérifie qu'un retrait est possible une seule fois avec un solde suffisant
TEST(AtmMachine, CanWithdrawSpecifyTimesReturnOnce) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  NiceMock<MockBankServer> mock_bankserver;

  // Définition des attentes
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
      .Times(AtMost(10))
      .WillOnce(Return(2000));

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result1 = atm_machine.Withdraw(account_number, withdraw_value);
  bool withdraw_result2 = atm_machine.Withdraw(account_number, withdraw_value);

  // Vérification
  EXPECT_TRUE(withdraw_result1); // Le premier retrait doit réussir
  EXPECT_FALSE(withdraw_result2); // Le second doit échouer (solde insuffisant)
}

//-----------------------------------------------------------------------------
// Test : Vérifie qu'un retrait est possible deux fois avec des soldes différents
TEST(AtmMachine, CanWithdrawSpecifyTimesReturnTwice) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  NiceMock<MockBankServer> mock_bankserver;

  // Définition des attentes
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
      .Times(AtMost(10))
      .WillOnce(Return(2000))  // Premier appel : 2000
      .WillOnce(Return(3000)); // Deuxième appel : 3000

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result1 = atm_machine.Withdraw(account_number, withdraw_value);
  bool withdraw_result2 = atm_machine.Withdraw(account_number, withdraw_value);

  // Vérification
  EXPECT_TRUE(withdraw_result1);
  EXPECT_TRUE(withdraw_result2);
}

//-----------------------------------------------------------------------------
// Test : Vérifie qu'un retrait est possible plusieurs fois avec un solde récurrent
TEST(AtmMachine, CanWithdrawSpecifyRepeatedly) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  NiceMock<MockBankServer> mock_bankserver;

  // Définition des attentes
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
      .Times(AtMost(10))
      .WillOnce(Return(2000))
      .WillRepeatedly(Return(3000)); // Toujours 3000 après le premier appel

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result1 = atm_machine.Withdraw(account_number, withdraw_value);
  bool withdraw_result2 = atm_machine.Withdraw(account_number, withdraw_value);

  // Vérification
  EXPECT_TRUE(withdraw_result1);
  EXPECT_TRUE(withdraw_result2);
}

//-----------------------------------------------------------------------------
// Test : Vérifie le retrait sans restriction sur le nombre d'appels
TEST(AtmMachine, CanWithdrawNoCardinality) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  NiceMock<MockBankServer> mock_bankserver;

  // Définition des attentes
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
      .WillRepeatedly(Return(2000)); // Toujours un solde de 2000   // On s'attend a ce que la fonction soit appeler au moins 0 fois (regarder la doc)

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result1 = atm_machine.Withdraw(account_number, withdraw_value);
  bool withdraw_result2 = atm_machine.Withdraw(account_number, withdraw_value);

  // Vérification
  EXPECT_TRUE(withdraw_result1);
  EXPECT_TRUE(withdraw_result2);
}

//-----------------------------------------------------------------------------
// Test désactivé : Vérifie qu'un retrait échoue sans valeur de retour définie
TEST(AtmMachine, DISABLED_CanWithdrawNoCardinality_noWillRepeatedly) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  NiceMock<MockBankServer> mock_bankserver;

  // Définition des attentes sans action définie
  EXPECT_CALL(mock_bankserver, GetBalance(account_number)); // Expect 1 Call uniquement

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result1 = atm_machine.Withdraw(account_number, withdraw_value);
  bool withdraw_result2 = atm_machine.Withdraw(account_number, withdraw_value); // LE test devrais ffail car appel 2 fois de GetBalence

  // Vérification
  EXPECT_FALSE(withdraw_result1);
  EXPECT_FALSE(withdraw_result2);
}

//-----------------------------------------------------------------------------
// Test désactivé : Vérifie un seul retrait réussi puis un échec
TEST(AtmMachine, DISABLED_CanWithdrawNoCardinality_noWillRepeatedly_WillOnce) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  NiceMock<MockBankServer> mock_bankserver;

  // Définition des attentes
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
      .WillOnce(Return(1000)); // Solde exact pour un seul retrait

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result1 = atm_machine.Withdraw(account_number, withdraw_value);
  bool withdraw_result2 = atm_machine.Withdraw(account_number, withdraw_value); // LE test devrais fail car appel 2 fois de GetBalence

  // Vérification
  EXPECT_TRUE(withdraw_result1);
  EXPECT_FALSE(withdraw_result2);
}

//-----------------------------------------------------------------------------
// Test : Vérifie qu'aucun débit n'est effectué si le solde est insuffisant
TEST(AtmMachine, CanWithdrawDisallowSomeCalls) {
  // Préparation
  const int account_number = 1234;
  NiceMock<MockBankServer> mock_bankserver;

  // Définition des attentes
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
      .Times(1)
      .WillOnce(Return(0));  // Solde insuffisant

  EXPECT_CALL(mock_bankserver, Debit(_, _)).Times(0);  // Aucun débit ne doit être effectué

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(account_number, 1000);

  // Vérification
  EXPECT_FALSE(withdraw_result);
}
