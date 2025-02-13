#include "gtest/gtest.h"

void Exit(int exitCode = 0) {
  // Exit with the given code.
  std::cout << "Abbas";
  std::exit(exitCode);
}

void Kill(int exitCode = SIGINT) {
  // Kill the process with the given code.
  kill(getpid(), exitCode);
}

TEST(MyDeathTest, Exit) {
  // Check if Exit() function exits with non-zero code.
  EXPECT_DEATH(Exit(1), "");
}

TEST(MyDeathTest, NormalExit) {
  EXPECT_EXIT(Exit(), testing::ExitedWithCode(0), "");
}

TEST(MyDeathTest, AbnormalExit) {
  EXPECT_EXIT(Exit(1), testing::ExitedWithCode(1), "");
}

TEST(MyDeathTest, KillProcess) {
  EXPECT_EXIT(Kill(SIGKILL), testing::KilledBySignal(SIGKILL), "");
}