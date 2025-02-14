#include "bankserver/atm_machine.h"
#include "bankserver/bankserver.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Gt;
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
// Test : Vérifie qu'un retrait est possible avec un solde suffisant
TEST(AtmMachine, CanWithdrawSimpleExpectation) {
    // Préparation
    const int account_number = 1234;
    const int withdraw_value = 1000;
    MockBankServer mock_bankserver;

    // Définition des attentes sur le mock
    EXPECT_CALL(mock_bankserver, GetBalance(account_number))
        .Times(AtLeast(1))  // L'appel doit être fait au moins une fois
        .WillRepeatedly(Return(2000));  // Retourne toujours un solde de 2000

    // Exécution
    AtmMachine atm_machine(&mock_bankserver);
    bool withdraw_result = atm_machine.Withdraw(account_number, withdraw_value);

    // Vérification
    EXPECT_TRUE(withdraw_result);  // Le retrait doit réussir
}

//-----------------------------------------------------------------------------
// Test : Vérifie qu'un retrait est possible avec un solde suffisant et un appel unique
TEST(AtmMachine, CanWithdrawSpecifyTimes) {
    // Préparation
    const int account_number = 1234;
    const int withdraw_value = 1000;
    MockBankServer mock_bankserver;

    // Définition des attentes sur le mock
    EXPECT_CALL(mock_bankserver, GetBalance(account_number))
        .Times(1)  // L'appel doit être fait exactement une fois
        .WillOnce(Return(2000));  // Retourne 2000 seulement une fois

    // Exécution
    AtmMachine atm_machine(&mock_bankserver);
    bool withdraw_result = atm_machine.Withdraw(account_number, withdraw_value);

    // Vérification
    EXPECT_TRUE(withdraw_result);  // Le retrait doit réussir
}

//-----------------------------------------------------------------------------
// Test : Vérifier l'ensemble du processus de retrait en s'assurant que toutes les étapes sont appelées
TEST(AtmMachine, CanWithdraw) {
    // Préparation
    const int account_number = 1234;
    const int withdraw_value = 1000;
    MockBankServer mock_bankserver;

    // Définition des attentes sur le mock pour simuler le comportement de l'ATM
    // Connexion unique


    // Vérification du solde effectuée une seule fois ET
    // Retourne un solde suffisant pour le retrait

    // Débit du montant demandé

    // Déconnexion après l'opération

    // Exécution


    // Vérification
    // Le retrait doit réussir
}
