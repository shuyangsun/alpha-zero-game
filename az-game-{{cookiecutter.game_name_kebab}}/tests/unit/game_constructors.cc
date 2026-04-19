#include <memory>
#include <utility>

#include "gtest/gtest.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__board}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_ptr}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_result}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

[[nodiscard]] {{cookiecutter.__game_ptr}} CreateGame(
    {{cookiecutter.__player}} starting_player = {{cookiecutter.__player}}{}) {
  {{cookiecutter.__game_result}} maybe_game =
      {{cookiecutter.__game_cls}}::Create(starting_player);
  if (!maybe_game.has_value()) {
    ADD_FAILURE() << "Create() returned an error.";
    return nullptr;
  }

  return std::move(*maybe_game);
}

void ExpectFreshGameState(const {{cookiecutter.__game_cls}}& game,
                          const {{cookiecutter.__player}}& expected_player) {
  EXPECT_EQ(game.GetBoard(), {{cookiecutter.__board}}{});
  EXPECT_EQ(game.CurrentRound(), 0u);
  EXPECT_EQ(game.CurrentPlayer(), expected_player);
  EXPECT_EQ(game.LastPlayer(), std::nullopt);
  EXPECT_FALSE(game.LastAction().has_value());
}

// TODO(TASK-006): delete this test if the default player constructor was deleted.
TEST(GameConstructors, DefaultConstructor) {
  {{cookiecutter.__game_result}} maybe_game =
      {{cookiecutter.__game_cls}}::Create();
  ASSERT_TRUE(maybe_game.has_value());

  {{cookiecutter.__game_ptr}} game = std::move(*maybe_game);
  ASSERT_NE(game, nullptr);
  ExpectFreshGameState(
      *static_cast<const {{cookiecutter.__game_cls}}*>(game.get()),
      {{cookiecutter.__player}}{});
}

TEST(GameConstructors, ExplicitStartingPlayer) {
  const {{cookiecutter.__player}} starting_player =
      static_cast<{{cookiecutter.__player}}>(true);

  {{cookiecutter.__game_ptr}} game = CreateGame(starting_player);
  ASSERT_NE(game, nullptr);

  ExpectFreshGameState(
      *static_cast<const {{cookiecutter.__game_cls}}*>(game.get()),
      starting_player);
}

TEST(GameConstructors, CopyConstructorPreservesState) {
  const {{cookiecutter.__player}} starting_player =
      static_cast<{{cookiecutter.__player}}>(true);
  {{cookiecutter.__game_ptr}} game = CreateGame(starting_player);
  ASSERT_NE(game, nullptr);

  const {{cookiecutter.__game_cls}}& original =
      *static_cast<const {{cookiecutter.__game_cls}}*>(game.get());
  {{cookiecutter.__game_cls}} copied_game(original);

  ExpectFreshGameState(copied_game, starting_player);
}

TEST(GameConstructors, MoveConstructorPreservesState) {
  const {{cookiecutter.__player}} starting_player =
      static_cast<{{cookiecutter.__player}}>(true);
  {{cookiecutter.__game_ptr}} game = CreateGame(starting_player);
  ASSERT_NE(game, nullptr);

  {{cookiecutter.__game_cls}} original_game(
      *static_cast<const {{cookiecutter.__game_cls}}*>(game.get()));
  {{cookiecutter.__game_cls}} moved_game(std::move(original_game));

  ExpectFreshGameState(moved_game, starting_player);
}

TEST(GameConstructors, CopyReturnsNullptrUntilImplemented) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  // TODO(TASK-100): update this assertion when Copy() is implemented.
  {{cookiecutter.__game_ptr}} copied_game = game->Copy();
  EXPECT_EQ(copied_game, nullptr);
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
