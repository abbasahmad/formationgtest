#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AllOf;
using ::testing::Args;
using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Gt;
using ::testing::Lt;
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
// Test : Tentative de retrait avec un solde nul
//Specification du comportement par defaut
TEST(AtmMachine, OnCallWithZero) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  MockBankServer mock_bankserver;

  // Configuration du comportement par défaut du mock
  ON_CALL(mock_bankserver, Connect).WillByDefault(Return());
  ON_CALL(mock_bankserver, Disconnect).WillByDefault(Return());
  ON_CALL(mock_bankserver, Debit).WillByDefault(Return());
  ON_CALL(mock_bankserver, Credit).WillByDefault(Return());
  ON_CALL(mock_bankserver, GetBalance).WillByDefault(Return(0));

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(account_number, withdraw_value);

  // Vérification : le retrait doit échouer
  EXPECT_FALSE(withdraw_result);
}

//-----------------------------------------------------------------------------
// Test : Vérification d’un retrait simple avec un solde suffisant
//On peut exclure les comportement par default
TEST(AtmMachine, CanWithdrawSimple) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  MockBankServer mock_bankserver;

  // Définition du solde pour le compte testé
  ON_CALL(mock_bankserver, GetBalance(account_number)).WillByDefault(Return(2000));

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(account_number, withdraw_value);
  //std::cout << withdraw_result << std::endl << " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl << std::endl << std::endl;
  // Vérification
  EXPECT_TRUE(withdraw_result);
}


//-----------------------------------------------------------------------------
// Test : Retrait avec un compte disposant d'un solde suffisant
TEST(AtmMachine, OnCallWithOneFunctionSpecified) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  MockBankServer mock_bankserver;

  // Configuration du comportement par défaut du mock
  ON_CALL(mock_bankserver, Connect).WillByDefault(Return());
  ON_CALL(mock_bankserver, Disconnect).WillByDefault(Return());
  ON_CALL(mock_bankserver, Debit).WillByDefault(Return());
  ON_CALL(mock_bankserver, Credit).WillByDefault(Return());
  ON_CALL(mock_bankserver, GetBalance(account_number)).WillByDefault(Return(2000));

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result1 = atm_machine.Withdraw(account_number, withdraw_value);
  bool withdraw_result2 = atm_machine.Withdraw(account_number + 1, withdraw_value);

  // Vérification
  EXPECT_TRUE(withdraw_result1);  // Devrait réussir
  EXPECT_FALSE(withdraw_result2); // Devrait échouer
}


//-----------------------------------------------------------------------------
// Test : Gestion de plusieurs comportements pour GetBalance
TEST(AtmMachine, OnCallWithOneFunctionSpecifiedTwice) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  MockBankServer mock_bankserver;

  // Définition du comportement de GetBalance (cas générique puis cas spécifique)
  ON_CALL(mock_bankserver, GetBalance).WillByDefault(Return(2000));
  ON_CALL(mock_bankserver, GetBalance(account_number)).WillByDefault(Return(1));

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result1 = atm_machine.Withdraw(account_number, withdraw_value);
  bool withdraw_result2 = atm_machine.Withdraw(account_number + 1, withdraw_value);

  // Vérification
  EXPECT_FALSE(withdraw_result1); // Devrait échouer car solde insuffisant
  EXPECT_TRUE(withdraw_result2);  // Devrait réussir
}


//-----------------------------------------------------------------------------
// Test : Vérification avec des correspondances génériques (wildcard)
TEST(AtmMachine, CanWithdrawSimpleWithWildcardMatcher) {
  // Préparation
  const int account_number = 1234;
  const int withdraw_value = 1000;
  MockBankServer mock_bankserver;

  // Définition des comportements avec des matchers pour différentes plages de valeurs
  ON_CALL(mock_bankserver, GetBalance(_)).WillByDefault(Return(2000));
  ON_CALL(mock_bankserver, GetBalance(Gt(1000))).WillByDefault(Return(2000));
  ON_CALL(mock_bankserver, GetBalance(AllOf(Gt(1000), Lt(2000)))).WillByDefault(Return(2000));

  ON_CALL(mock_bankserver, DoubleTransaction(_, _, _))
    .With(AllOf(Args<0, 1>(Gt()), Args<1, 2>(Gt())))
    .WillByDefault(Return(true));

  // Exécution
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(account_number, withdraw_value);

  // Vérification
  EXPECT_TRUE(withdraw_result);
}

//-----------------------------------------------------------------------------
//CREER une classe pour l'utiliser dans une fixture de test TEST_F
//LE SetUp retourne une valeur "1000" quand on appelle la fonction GetBalence
//Noublier pas de declarer votre MockBankServer !
//Ensuite ajouter 1 ou 2 TEST_F

