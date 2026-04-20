#include "gtest/gtest.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

TEST(GameState, CanonicalBoardReturnsExpectedView) {
  GTEST_SKIP() << "TODO(TASK-GAME-STATE-TEST): verify CanonicalBoard() for the current player.";
}

TEST(GameState, IsOverReturnsFalseAtStart) {
  GTEST_SKIP() << "TODO(TASK-GAME-STATE-TEST): verify the initial game is not over.";
}

TEST(GameState, GetScoreReturnsExpectedTerminalScores) {
  GTEST_SKIP() << "TODO(TASK-GAME-STATE-TEST): verify terminal scores for each player.";
}

TEST(GameConstructors, CopyPreservesState) {
  GTEST_SKIP() << "TODO(TASK-GAME-STATE-TEST): verify Copy() returns an equivalent game.";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
