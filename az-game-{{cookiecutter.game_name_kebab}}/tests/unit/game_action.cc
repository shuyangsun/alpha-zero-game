#include "gtest/gtest.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

// TODO(TASK-GAME-ACTION-TEST): add tests for `ValidActionsInto`,
// `PolicyIndex`, `ApplyActionInPlace`, and `UndoLastAction`. Make sure
// test names are meaningful but not too long.

TEST(GameAction, ValidActionsInto1) {
  GTEST_SKIP() << "TODO(TASK-GAME-ACTION-TEST): verify ValidActionsInto() "
                  "count and contents for the initial state.";
}

TEST(GameAction, ApplyActionInPlace1) {
  GTEST_SKIP() << "TODO(TASK-GAME-ACTION-TEST): verify ApplyActionInPlace() for a valid action.";
}

TEST(GameAction, UndoLastActionRestoresState) {
  GTEST_SKIP() << "TODO(TASK-GAME-ACTION-TEST): verify UndoLastAction() restores the previous state.";
}

TEST(GameAction, PolicyIndexIsBijection) {
  GTEST_SKIP() << "TODO(TASK-GAME-ACTION-TEST): verify PolicyIndex() is a bijection over the action space.";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
