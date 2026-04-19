#include <memory>
#include <utility>
#include <vector>

#include "gtest/gtest.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__action}};
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

TEST(GameAction, ValidActionsReturnsEmptyVectorInTemplateStub) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  const std::vector<{{cookiecutter.__action}}> actions = game->ValidActions();
  EXPECT_TRUE(actions.empty());
}

TEST(GameAction, GameAfterActionReturnsNullptrUntilImplemented) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  const {{cookiecutter.__action}} action = {{cookiecutter.__action}}{};

  // TODO(TASK-100): update this assertion when GameAfterAction() is
  // implemented.
  {{cookiecutter.__game_ptr}} next_game = game->GameAfterAction(action);
  EXPECT_EQ(next_game, nullptr);
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
