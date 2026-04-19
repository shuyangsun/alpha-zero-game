#include "gtest/gtest.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

TEST(GameBasic, GetBoardReturnsInitialBoard) {
  GTEST_SKIP() << "TODO(TASK-100): verify the initial board state.";
}

TEST(GameBasic, CurrentRoundStartsAtZero) {
  GTEST_SKIP() << "TODO(TASK-100): verify the initial round.";
}

TEST(GameBasic, CurrentPlayerMatchesStartingPlayer) {
  GTEST_SKIP() << "TODO(TASK-100): verify the starting player.";
}

TEST(GameBasic, LastPlayerStartsEmpty) {
  GTEST_SKIP() << "TODO(TASK-100): verify LastPlayer() before any action.";
}

TEST(GameBasic, LastActionStartsEmpty) {
  GTEST_SKIP() << "TODO(TASK-100): verify LastAction() before any action.";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
