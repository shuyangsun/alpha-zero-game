#include <memory>
#include <optional>
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

TEST(GameBasic, GetBoardStartsAsDefaultConstructedBoard) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  const {{cookiecutter.__board}}& board = game->GetBoard();
  EXPECT_EQ(board, {{cookiecutter.__board}}{});
}

TEST(GameBasic, CurrentRoundStartsAtZero) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  EXPECT_EQ(game->CurrentRound(), 0u);
}

TEST(GameBasic, CurrentPlayerMatchesStartingPlayer) {
  const {{cookiecutter.__player}} starting_player =
      static_cast<{{cookiecutter.__player}}>(true);
  {{cookiecutter.__game_ptr}} game = CreateGame(starting_player);
  ASSERT_NE(game, nullptr);

  EXPECT_EQ(game->CurrentPlayer(), starting_player);
}

TEST(GameBasic, LastPlayerStartsEmpty) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  EXPECT_EQ(game->LastPlayer(), std::nullopt);
}

TEST(GameBasic, LastActionStartsEmpty) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  EXPECT_EQ(game->LastAction(), std::nullopt);
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
