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
using ::testing::Assign;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Exactly;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::ThrowsMessage;
using ::testing::Unused;
using ::testing::WithArgs;

//-----------------------------------------------------------------------------
// Fonctions utilisées pour tester `Invoke`, `InvokeWithoutArgs` et les lambdas
void PrintHello() { 
  std::cout << "Hello!" << std::endl;
}

double Square(double x) { return (x * x); }

int Sum(int x, int y) { return x + y; }

int Return10000() { return 10000; }

// Classe Helper avec des méthodes statiques pour simuler des traitements complexes
class Helper {
public:
  static int ComplexJobSingleParameter(int x) { return (x * x); }
  static int ComplexJobMultiParameter(int x, int y, int z) {
    return (x * y * z);
  }
};

//-----------------------------------------------------------------------------
// Teste les différentes façons d'utiliser `Invoke` et `InvokeWithoutArgs`
TEST(AtmMachine, CanWithdrawWithMultipleInvoke) {
  // Arrange : Définition des paramètres du test
  const int account_number = 1234;
  const int withdraw_value = 1000;
  const int number_of_calls = 11;

  // Utilisation de NiceMock pour éviter les avertissements sur les appels non attendus
  NiceMock<MockBankServer> mock_bankserver;

  // Expectations : Définition de comportements variés pour `GetBalance`
  EXPECT_CALL(mock_bankserver, GetBalance(account_number))
    .Times(number_of_calls)
    .WillOnce(Invoke(Square))  // Appelle la fonction Square (x²) avec la meme valeur qui a été donner a GetBalance
    .WillOnce(Square)  // Syntaxe alternative pour appeler Square
    .WillOnce(DoAll(InvokeWithoutArgs(PrintHello), Return(1000)))  // Affiche "Hello!" puis retourne 1000 notez que printHello ne prend pas d'argument
    .WillOnce([](int n) { return Square(n); })  // Utilisation d'une lambda pour appeler Square n = account_number
    .WillOnce([](int n) { return Sum(n, 1000); })  // Lambda qui additionne n + 1000
    .WillOnce([]() { return Return10000(); })  // Lambda qui retourne 10000
    .WillOnce(Return10000)  // Appelle directement Return10000
    .WillRepeatedly(Return(Return10000()));  // Retourne toujours 10000 après les appels définis

  // Expectations : Simulation du comportement de `Debit`
  EXPECT_CALL(mock_bankserver, Debit(account_number, withdraw_value))
    .WillRepeatedly(Invoke([](int a, int w) {
    std::cout << "a: " << a << ", w: " << w << std::endl;
      }));  // Affiche les arguments passés à Debit

  // Act : Effectuer plusieurs retraits pour tester tous les comportements définis
  AtmMachine atm_machine(&mock_bankserver);
  bool withdraw_result = true;
  for (int i = 0; i < number_of_calls; i++) {
    withdraw_result =
      withdraw_result && atm_machine.Withdraw(account_number, withdraw_value);
  }

  // Assert : Vérification que tous les retraits ont bien réussi
  EXPECT_TRUE(withdraw_result);
}
