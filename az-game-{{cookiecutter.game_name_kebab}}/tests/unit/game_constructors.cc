#include "gtest/gtest.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__board}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

// TODO(TASK-GAME-CONSTRUCTOR-TEST): delete this test if the default
// constructor was deleted.
TEST(GameConstructors, DefaultConstructor) {
  {{cookiecutter.__game_cls}} game;
  EXPECT_EQ(game.GetBoard(), {{cookiecutter.__board}}{});
  EXPECT_EQ(game.CurrentRound(), 0u);
  EXPECT_EQ(game.CurrentPlayer(), {{cookiecutter.__player}}{});
  EXPECT_EQ(game.LastPlayer(), std::nullopt);
  EXPECT_FALSE(game.LastAction().has_value());
}

TEST(GameConstructors, ExplicitStartingPlayer) {
  GTEST_SKIP() << "TODO(TASK-GAME-CONSTRUCTOR-TEST): verify the explicit-starting-player constructor.";
}

TEST(GameConstructors, CopyConstructorPreservesState) {
  GTEST_SKIP() << "TODO(TASK-GAME-CONSTRUCTOR-TEST): verify the copy constructor preserves state.";
}

TEST(GameConstructors, MoveConstructorPreservesState) {
  GTEST_SKIP() << "TODO(TASK-GAME-CONSTRUCTOR-TEST): verify the move constructor preserves state.";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
