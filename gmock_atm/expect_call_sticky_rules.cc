#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

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
// Importation des fonctionnalités de Google Mock utilisées dans les tests
using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Assign;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Exactly;
using ::testing::Gt;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::ThrowsMessage;
using ::testing::Unused;
using ::testing::WithArgs;

//-----------------------------------------------------------------------------
// Teste un cas où différentes règles d'attente ne se chevauchent pas.
//GooGle Mock matches les EXPECT_THAT DE BAS EN HAUT, LAST-IN - FIRST-OUT
TEST(AtmMachine, CanWithdrawNonOverlapping) {
    // Arrange
    const int withdraw_value = 1000;
    NiceMock<MockBankServer> mock_bankserver;

    // Expectations
    // - Pour les comptes supérieurs à 1234, GetBalance retournera toujours 2000.
    EXPECT_CALL(mock_bankserver, GetBalance(Gt(1234)))
        .Times(AnyNumber())
        .WillRepeatedly(Return(2000));

    // - Pour le compte 1234 précisément, GetBalance retournera 1000.
    EXPECT_CALL(mock_bankserver, GetBalance(1234))
        .Times(1)
        .WillOnce(Return(1000));

    // Act
    AtmMachine atm_machine(&mock_bankserver);
    auto result1 = atm_machine.Withdraw(1234, withdraw_value);
    auto result2 = atm_machine.Withdraw(5678, withdraw_value);

    // Assert
    EXPECT_TRUE(result1);  // Le retrait du compte 1234 doit réussir
    EXPECT_TRUE(result2);  // Le retrait du compte 5678 doit aussi réussir
}

//-----------------------------------------------------------------------------
// Ce test est désactivé car il échoue à cause de la "stickiness" des règles.
TEST(AtmMachine, DISABLED_CanWithdraw_MultipleCalls) {
    // Arrange
    const int account_number = 1234;
    const int withdraw_value = 1000;
    NiceMock<MockBankServer> mock_bankserver;

    // Expectations
    EXPECT_CALL(mock_bankserver, GetBalance(account_number))
        .Times(1)
        .WillOnce(Return(1000));

    EXPECT_CALL(mock_bankserver, GetBalance(account_number))
        .Times(1)
        .WillOnce(Return(2000));

    // Act
    AtmMachine atm_machine(&mock_bankserver);
    auto result1 = atm_machine.Withdraw(account_number, withdraw_value);
    auto result2 = atm_machine.Withdraw(account_number, withdraw_value);

    // Assert
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
}

//-----------------------------------------------------------------------------
// Correction du test précédent en utilisant `RetiresOnSaturation()`
TEST(AtmMachine, CanWithdraw_MultipleCalls_Retire) {
    // Arrange
    const int account_number = 1234;
    const int withdraw_value = 1000;
    NiceMock<MockBankServer> mock_bankserver;

    // Expectations
    EXPECT_CALL(mock_bankserver, GetBalance(account_number))
        .Times(1)
        .WillOnce(Return(1000));

    // Une fois que cette expectation est utilisée, elle sera retirée.
    EXPECT_CALL(mock_bankserver, GetBalance(account_number))
        .Times(1)
        .WillOnce(Return(2000))
        .RetiresOnSaturation();

    // Act
    AtmMachine atm_machine(&mock_bankserver);
    auto result1 = atm_machine.Withdraw(account_number, withdraw_value);
    auto result2 = atm_machine.Withdraw(account_number, withdraw_value);

    // Assert
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
}

//-----------------------------------------------------------------------------
// Test utilisant `WillOnce` pour retourner plusieurs valeurs consécutivement Une Meilleur façon de faire cela
TEST(AtmMachine, CanWithdraw_MultipleCalls_WillOnce) {
    // Arrange
    const int account_number = 1234;
    const int withdraw_value = 1000;
    NiceMock<MockBankServer> mock_bankserver;

    // Expectations : `WillOnce` retourne 1000, puis 2000 au deuxième appel.
    EXPECT_CALL(mock_bankserver, GetBalance(account_number))
        .Times(2)
        .WillOnce(Return(1000))
        .WillOnce(Return(2000));

    // Act
    AtmMachine atm_machine(&mock_bankserver);
    auto result1 = atm_machine.Withdraw(account_number, withdraw_value);
    auto result2 = atm_machine.Withdraw(account_number, withdraw_value);

    // Assert
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
}

//-----------------------------------------------------------------------------
// Test sur la priorité des règles générales et spécifiques
TEST(AtmMachine, CanWithdraw_GenericRuleFirst_Retire) {
    // Arrange
    const int account_number = 1234;
    const int withdraw_value = 1000;
    NiceMock<MockBankServer> mock_bankserver;

    // Expectations : règle générale d'abord (s'applique à tous les comptes)
    EXPECT_CALL(mock_bankserver, GetBalance(_))
        .Times(1)
        .WillRepeatedly(Return(2000));

    // Règle spécifique pour le compte 1234 qui ne sera utilisée qu'une fois.
    EXPECT_CALL(mock_bankserver, GetBalance(account_number))
        .Times(1)
        .WillOnce(Return(1000))
        .RetiresOnSaturation();

    // Act
    AtmMachine atm_machine(&mock_bankserver);
    auto result1 = atm_machine.Withdraw(account_number, withdraw_value);
    auto result2 = atm_machine.Withdraw(account_number, withdraw_value);

    // Assert
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
}

//-----------------------------------------------------------------------------
// Test qui génère des valeurs dynamiques pour `GetBalance`
TEST(AtmMachine, CanWithdraw_RetireStickyRules) {
    // Arrange
    const int account_number = 1234;
    const int withdraw_value = 1000;
    const int number_of_calls = 10;
    NiceMock<MockBankServer> mock_bankserver;

    // Expectations : Chaque appel à GetBalance retourne une valeur différente.
    for (int i = 0; i < number_of_calls; i++) {
        EXPECT_CALL(mock_bankserver, GetBalance(_))
            .Times(1)
            .WillOnce(Return(1000 + i))
            .RetiresOnSaturation();  // La règle disparaît après avoir été utilisée.
    }

    // Act
    AtmMachine atm_machine(&mock_bankserver);
    bool withdraw_result = true;
    for (int i = 0; i < number_of_calls; i++) {
        withdraw_result = withdraw_result &&
            atm_machine.Withdraw(account_number + i, withdraw_value);
    }

    // Assert
    EXPECT_TRUE(withdraw_result);
}
