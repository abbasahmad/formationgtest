#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"


//Parcourir avec le formateur
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

// Importation des utilitaires de Google Mock pour les tests
using ::testing::_;  // Correspond à n'importe quelle valeur
using ::testing::Gt;  // Vérifie si une valeur est supérieure à un seuil
using ::testing::Lt;  // Vérifie si une valeur est inférieure à un seuil

using ::testing::AllArgs;
using ::testing::AllOf;  // Combine plusieurs conditions
using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::ThrowsMessage;

//-----------------------------------------------------------------------------
// Test : Vérifie le retrait avec une correspondance générique pour GetBalance
TEST(AtmMachine, CanWithdrawWithMatchers1) {
  // Préparation
  MockBankServer mock_bankserver;

  // Définition des attentes sur le mock
  EXPECT_CALL(mock_bankserver, Connect()).Times(1);  // Connexion unique
  EXPECT_CALL(mock_bankserver, GetBalance(_)).Times(1).WillOnce(Return(2000));  // Solde suffisant
  EXPECT_CALL(mock_bankserver, Debit(_, _)).Times(1);  // Débit attendu
  EXPECT_CALL(mock_bankserver, Disconnect()).Times(1);  // Déconnexion unique

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Vérification
  EXPECT_TRUE(withdraw_result);
}

//-----------------------------------------------------------------------------
// Test : Vérifie le retrait avec des valeurs spécifiques pour GetBalance et Debit
TEST(AtmMachine, CanWithdrawWithMatchers2) {
  // Préparation
  MockBankServer mock_bankserver;

  // Définition des attentes
  EXPECT_CALL(mock_bankserver, Connect()).Times(1);
  EXPECT_CALL(mock_bankserver, GetBalance(Gt(1000)))  // Vérifie que le solde est supérieur à 1000
      .Times(1)
      .WillOnce(Return(2000));
  EXPECT_CALL(mock_bankserver, Debit(_, Lt(10000))).Times(1);  // Débit inférieur à 10 000
  EXPECT_CALL(mock_bankserver, Disconnect()).Times(1);

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Vérification
  EXPECT_TRUE(withdraw_result);
}

//-----------------------------------------------------------------------------
// Test : Vérifie le retrait avec des matchers multi-arguments
TEST(AtmMachine, CanWithdrawWithMultiArgumentMatchers) {

  // Préparation
  MockBankServer mock_bankserver;
  // Définition des attentes
  EXPECT_CALL(mock_bankserver, GetBalance(_)).Times(1).WillOnce(Return(2000));  // Solde suffisant
  //Le .With() va comparer nos parametre les un par rapport au autres
  EXPECT_CALL(mock_bankserver, Debit(_, _)).With(Gt()).Times(1);  // Vérifie que la transaction est effectuée avec un numero de compte en banque plus grand que le montant

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Vérification
  EXPECT_TRUE(withdraw_result);
}

//-----------------------------------------------------------------------------
// Test : Vérifie le retrait avec des matchers composés (conditions multiples)
TEST(AtmMachine, CanWithdrawWithCompositMatchers) {
  // Préparation
  MockBankServer mock_bankserver;

  // Définition des attentes
  EXPECT_CALL(mock_bankserver, Connect()).Times(1);
  EXPECT_CALL(mock_bankserver, GetBalance(AllOf(Gt(1000), Lt(10000))))  // Solde entre 1000 et 10 000
      .Times(1)
      .WillOnce(Return(2000));
  EXPECT_CALL(mock_bankserver, Debit(_, Lt(10000))).Times(1);  // Débit inférieur à 10 000
  EXPECT_CALL(mock_bankserver, Disconnect()).Times(1);

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Vérification
  EXPECT_TRUE(withdraw_result);
}

//-----------------------------------------------------------------------------
// Test : Vérifie le retrait sans tenir compte des arguments des fonctions
TEST(AtmMachine, CanWithdrawIgnoreArguments) {

  // Préparation
  MockBankServer mock_bankserver;

  // Définition des attentes
  EXPECT_CALL(mock_bankserver, Connect).Times(1);  // Connexion unique
  EXPECT_CALL(mock_bankserver, GetBalance).Times(1).WillOnce(Return(2000));  // Solde suffisant
  EXPECT_CALL(mock_bankserver, Debit).Times(1);  // Débit sans contrainte d'argument
  EXPECT_CALL(mock_bankserver, Disconnect).Times(1);  // Déconnexion unique

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Vérification
  EXPECT_TRUE(withdraw_result);
}
