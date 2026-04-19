#include <utility>

#include "gtest/gtest.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__board}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_result}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

// TODO(TASK-006): delete this test if the default player constructor was deleted.
TEST(GameConstructors, DefaultConstructor) {
  {{cookiecutter.__game_result}} maybe_game =
      {{cookiecutter.__game_cls}}::Create();
  ASSERT_TRUE(maybe_game.has_value());

  auto game = std::move(*maybe_game);
  ASSERT_NE(game, nullptr);

  const auto& concrete_game =
      *static_cast<const {{cookiecutter.__game_cls}}*>(game.get());
  EXPECT_EQ(concrete_game.GetBoard(), {{cookiecutter.__board}}{});
  EXPECT_EQ(concrete_game.CurrentRound(), 0u);
  EXPECT_EQ(concrete_game.CurrentPlayer(), {{cookiecutter.__player}}{});
  EXPECT_EQ(concrete_game.LastPlayer(), std::nullopt);
  EXPECT_FALSE(concrete_game.LastAction().has_value());
}

TEST(GameConstructors, ExplicitStartingPlayer) {
  GTEST_SKIP() << "TODO(TASK-100): verify Create(starting_player).";
}

TEST(GameConstructors, CopyConstructorPreservesState) {
  GTEST_SKIP() << "TODO(TASK-100): verify the copy constructor preserves state.";
}

TEST(GameConstructors, MoveConstructorPreservesState) {
  GTEST_SKIP() << "TODO(TASK-100): verify the move constructor preserves state.";
}

TEST(GameConstructors, CopyPreservesState) {
  GTEST_SKIP() << "TODO(TASK-100): verify Copy() returns an equivalent game.";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
