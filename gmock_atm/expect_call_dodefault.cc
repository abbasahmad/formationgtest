#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

// Importation des fonctionnalités de Google Mock permettant de définir des attentes et des comportements simulés
using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AtLeast;
using ::testing::AtMost;
using ::testing::DoDefault;
using ::testing::Exactly;
using ::testing::Gt;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::ThrowsMessage;

//-----------------------------------------------------------------------------
// Classe Mock qui simule le comportement du serveur bancaire.
// Elle permet de tester l'ATM sans dépendre d'un serveur réel.
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
// Classe de test qui utilise un mock et définit un comportement par défaut.
// Elle évite de devoir répéter certaines configurations dans chaque test.
class DoDefaultTest : public ::testing::Test {
 public:
  void SetUp() override {
    // Définition d'un comportement par défaut pour GetBalance.
    // Si GetBalance est appelé sans expectation explicite, il retournera 1000.
    ON_CALL(mock_bankserver_, GetBalance).WillByDefault(Return(1000));
  }

  NiceMock<MockBankServer> mock_bankserver_;
};

//-----------------------------------------------------------------------------
// Teste si l'ATM permet un retrait lorsque le solde par défaut est suffisant.

TEST_F(DoDefaultTest, CanWithdraw) {
  // Arrange : Définition des variables de test
  const int account_number = 1234;
  const int withdraw_value = 1000;

  NiceMock<MockBankServer> mock_bankserver;

  // Expectations : Utilisation de DoDefault() pour respecter le comportement par défaut
  EXPECT_CALL(mock_bankserver_, GetBalance(account_number))
      .WillRepeatedly(DoDefault());

  // Act : Tentative de retrait
  AtmMachine atm_machine(&mock_bankserver_);
  bool withdraw_result = atm_machine.Withdraw(account_number, withdraw_value);

  // Assert : Le retrait doit réussir puisque le solde par défaut est 1000
  EXPECT_TRUE(withdraw_result);
}

//-----------------------------------------------------------------------------
// Teste si l'ATM empêche un retrait lorsque le solde est insuffisant.

TEST_F(DoDefaultTest, CannotWithdraw) {
  // Arrange
  const int account_number = 1234;
  const int withdraw_value = 1000;

  NiceMock<MockBankServer> mock_bankserver;

  // Expectations : Cette fois, on définit un solde insuffisant (0)
  //On ecrase le DoDefault
  EXPECT_CALL(mock_bankserver_, GetBalance(account_number))
      .WillRepeatedly(Return(0));

  // Act : Tentative de retrait
  AtmMachine atm_machine(&mock_bankserver_);
  bool withdraw_result = atm_machine.Withdraw(account_number, withdraw_value);

  // Assert : Le retrait doit échouer car le solde est insuffisant
  EXPECT_FALSE(withdraw_result);
}
