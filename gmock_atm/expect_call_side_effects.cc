#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

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

// Importation des fonctionnalités de Google Mock utilisées dans les tests
using ::testing::_;
using ::testing::Assign;
using ::testing::DoAll;
using ::testing::Gt;
using ::testing::Lt;
using ::testing::Return;
using ::testing::SaveArg;
using ::testing::SetErrnoAndReturn;
using ::testing::StrEq;
using ::testing::Throw;
using ::testing::Throws;
using ::testing::ThrowsMessage;

// Exception personnalisée utilisée dans certains tests
class InvalidValueException : public virtual std::exception {
public:
    const char* what() const noexcept override { return "Invalid value"; }
};

//-----------------------------------------------------------------------------
// Teste si un retrait est correctement enregistré avec des effets de bord
// - Utilisation de `SaveArg` pour stocker les arguments de l'appel `Debit`
// - Utilisation de `Assign` pour modifier une variable de test après un appel
TEST(AtmMachine, CanWithdrawSideEffect) {
    bool done = false;  // Variable pour vérifier l'exécution de Disconnect
    int account_number;
    int value;

    // Arrange
    MockBankServer mock_bankserver;

    // Expectations
    // - `SaveArg<0>(&account_number)` enregistre le premier argument passé à Debit
    // - `SaveArg<1>(&value)` enregistre le second argument passé à Debit
    EXPECT_CALL(mock_bankserver, Debit(_, _))
        .Times(1)
        .WillOnce(DoAll(SaveArg<0>(&account_number), SaveArg<1>(&value)));

    // - `Assign(&done, true)` assigne true à `done` lorsqu'on appelle Disconnect
    EXPECT_CALL(mock_bankserver, Disconnect())
        .Times(1)
        .WillOnce(Assign(&done, true));

    // - `Return(1000)` fait en sorte que GetBalance retourne 1000
    EXPECT_CALL(mock_bankserver, GetBalance(1234))
        .Times(1)
        .WillOnce(Return(1000));

    // Act
    AtmMachine atm_machine(&mock_bankserver);
    bool withdraw_result = atm_machine.Withdraw(1234, 1000);

    // Assert
    EXPECT_TRUE(withdraw_result);  // Le retrait doit réussir

    // Vérifier que Disconnect a bien été appelé
    //...

    // Vérifier que le bon compte a été débité
    //...

    // Vérifier que le bon montant a été débité
    //...
}

//-----------------------------------------------------------------------------
// Teste le comportement lorsqu'une erreur système (errno) est déclenchée
// - Utilisation de `SetErrnoAndReturn` pour simuler une erreur système avec `errno`
TEST(AtmMachine, CanWithdrawSideEffectErrno) {
    // Arrange
    MockBankServer mock_bankserver;
    errno = 0;  // Réinitialisation de errno avant le test

    // Expectations
    // Simule une erreur en définissant `errno` à `EINVAL`(Error INVALind) et retourne 0
    EXPECT_CALL(mock_bankserver, GetBalance(4567))
        .Times(1)
        .WillOnce(SetErrnoAndReturn(EINVAL, 0));

    // Act
    AtmMachine atm_machine(&mock_bankserver);
    bool withdraw_result = atm_machine.Withdraw(4567, 1000);

    // Assert
    EXPECT_FALSE(withdraw_result);  // Le retrait doit échouer à cause de l'erreur

    // Vérifier que errno a bien été mis à EINVAL
    //...
}

//-----------------------------------------------------------------------------
// Teste le comportement de l'ATM lorsque le serveur bancaire lève une exception
TEST(AtmMachine, ThrowException) {
    // Arrange
    const int account_number = 1234;
    const int withdraw_value = 1000;
    MockBankServer mock_bankserver;

    // Expectations

    // Faite en sorte que Connect lève une exception InvalidValueException() a chaque appel
    //...
    

    // Act and Assert
    AtmMachine atm_machine(&mock_bankserver);

    // Vérifie qu'un appel à Withdraw lève bien `InvalidValueException`
    EXPECT_THROW(atm_machine.Withdraw(account_number, withdraw_value),
        InvalidValueException);

    // Vérifie la levée d'exception avec `Throws`
    EXPECT_THAT([&]() { atm_machine.Withdraw(account_number, withdraw_value); },
        Throws<InvalidValueException>());

    // Vérifie que l'exception levée contient bien le message "Invalid value"
    EXPECT_THAT([&]() { atm_machine.Withdraw(account_number, withdraw_value); },
        ThrowsMessage<InvalidValueException>(StrEq("Invalid value")));
}
