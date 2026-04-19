#include "gtest/gtest.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

TEST(GameAction, ValidActionsReturnsExpectedInitialActions) {
  GTEST_SKIP() << "TODO(TASK-100): verify ValidActions() for the initial state.";
}

TEST(GameAction, GameAfterActionReturnsExpectedNextState) {
  GTEST_SKIP() << "TODO(TASK-100): verify GameAfterAction() for a valid action.";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
