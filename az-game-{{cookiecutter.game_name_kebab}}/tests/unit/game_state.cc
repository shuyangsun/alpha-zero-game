#include "gtest/gtest.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

TEST(GameState, CanonicalBoardReturnsExpectedView) {
  GTEST_SKIP() << "TODO(TASK-100): verify CanonicalBoard() for the current player.";
}

TEST(GameState, IsOverReturnsFalseAtStart) {
  GTEST_SKIP() << "TODO(TASK-100): verify the initial game is not over.";
}

TEST(GameState, GetScoreReturnsExpectedTerminalScores) {
  GTEST_SKIP() << "TODO(TASK-100): verify terminal scores for each player.";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
