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

TEST(GameState, CanonicalBoardMatchesBoardForTemplateStub) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  const {{cookiecutter.__board}} canonical_board = game->CanonicalBoard();
  EXPECT_EQ(canonical_board, game->GetBoard());
}

TEST(GameState, IsOverReturnsFalseAtStart) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  EXPECT_FALSE(game->IsOver());
}

TEST(GameState, GetScoreReturnsZeroForBothPlayersInTemplateStub) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  EXPECT_FLOAT_EQ(game->GetScore({{cookiecutter.__player}}{}), 0.0f);
  EXPECT_FLOAT_EQ(
      game->GetScore(static_cast<{{cookiecutter.__player}}>(true)), 0.0f);
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
