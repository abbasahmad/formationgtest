#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

// Classe mock permettant de simuler le comportement du serveur bancaire
// afin de tester l'ATM sans avoir besoin d'un serveur réel.
class MockBankServer : public BankServer {
 public:
  MOCK_METHOD(void, Connect, (), (override));
  MOCK_METHOD(void, Disconnect, (), (override));
  MOCK_METHOD(void, Credit, (int, int), (override));
  MOCK_METHOD(void, Debit, (int, int), (override));
  MOCK_METHOD(bool, DoubleTransaction, (int, int, int), (override));
  MOCK_METHOD(int, GetBalance, (int), (const, override));
};

using ::testing::_;
using ::testing::Expectation;
using ::testing::Gt;
using ::testing::Lt;
using ::testing::Sequence;

using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::ThrowsMessage;

TEST(AtmMachine, CanWithdrawExpectInAnyOrder) {
  // Teste si un retrait est possible sans imposer d'ordre spécifique aux appels.

  // Arrange : Création du mock et définition des attentes.
  MockBankServer mock_bankserver;

  // Définition des appels attendus et de leurs comportements simulés.
  EXPECT_CALL(mock_bankserver, GetBalance(_)).Times(1).WillOnce(Return(2000));
  EXPECT_CALL(mock_bankserver, Connect()).Times(1);
  EXPECT_CALL(mock_bankserver, Debit(_, _)).Times(1);
  EXPECT_CALL(mock_bankserver, Disconnect()).Times(1);

  // Act : Création de l'ATM et tentative de retrait.
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Assert : Vérification du résultat attendu.
  EXPECT_TRUE(withdraw_result);
}

TEST(AtmMachine, CanWithdrawForceSequence) {
  // Ce test impose un ordre strict sur l'exécution des appels mockés.
  //Essayer de changer l'ordre d'apparence dans le test de vos EXPECT_CALL et regarder le rapport de test
  InSequence seq;

  // Arrange
  MockBankServer mock_bankserver;

  // Définition des attentes dans un ordre précis parceque on a declaré InSquence seq;
  EXPECT_CALL(mock_bankserver, Connect()).Times(1);
  EXPECT_CALL(mock_bankserver, GetBalance(_)).Times(1).WillOnce(Return(2000));
  EXPECT_CALL(mock_bankserver, Debit(_, _)).Times(1);
  EXPECT_CALL(mock_bankserver, Disconnect()).Times(1);

  // Act
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Assert
  EXPECT_TRUE(withdraw_result);
}

TEST(AtmMachine, CanWithdrawForceSequenceOnSomeCalls) {
  // Test impose une séquence seulement sur certains appels avec de l'imbrication

  // Arrange
  MockBankServer mock_bankserver;

  // Certains appels sont forcés dans un ordre donné.
  {
    InSequence seq;
    EXPECT_CALL(mock_bankserver, Debit(_, _)).Times(1);
    EXPECT_CALL(mock_bankserver, Disconnect()).Times(1);
  }

  // Une autre séquence est appliquée à d'autres appels.
  {
    InSequence seq;
    EXPECT_CALL(mock_bankserver, Connect()).Times(1);
    EXPECT_CALL(mock_bankserver, GetBalance(_)).Times(1).WillOnce(Return(2000));
  }

  // Act
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Assert
  EXPECT_TRUE(withdraw_result);
}

TEST(AtmMachine, CanWithdrawExpectForcePartialOrderUsingSequence) {
  // Ce test vérifie que Connect est appelé avant Disconnect,
  // mais ne force pas d'ordre strict sur les autres appels.

  Sequence s1, s2;

  // Arrange
  MockBankServer mock_bankserver;

  // Certains appels doivent respecter un ordre particulier.
  EXPECT_CALL(mock_bankserver, Connect()).Times(1).InSequence(s1);
  EXPECT_CALL(mock_bankserver, Debit(_, _)).Times(1);
  EXPECT_CALL(mock_bankserver, GetBalance(_)).Times(1).WillOnce(Return(2000));
  EXPECT_CALL(mock_bankserver, Disconnect()).Times(1).InSequence(s1);

  // Act
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Assert
  EXPECT_TRUE(withdraw_result);
}


//EXPECTATION et AFTER

TEST(AtmMachine, CanWithdrawExpectForcePartialOrderWithAfter) {
  // Test impose que Disconnect soit appelé après Connect et Debit.

  // Arrange
  MockBankServer mock_bankserver;

  // On stocke les attentes sous forme d'objets Expectation pour forcer l'ordre.
  Expectation e_connect = EXPECT_CALL(mock_bankserver, Connect()).Times(1);
  Expectation e_debit = EXPECT_CALL(mock_bankserver, Debit(_, _)).Times(1);

  // Disconnect ne peut être exécuté qu'après les attentes précédentes.
  EXPECT_CALL(mock_bankserver, Disconnect()).Times(1).After(e_connect, e_debit);

  // GetBalance peut être exécuté indépendamment.
  EXPECT_CALL(mock_bankserver, GetBalance(_)).Times(1).WillOnce(Return(2000));

  // Act
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = atm_machine.Withdraw(1234, 1000);

  // Assert
  EXPECT_TRUE(withdraw_result);
}
