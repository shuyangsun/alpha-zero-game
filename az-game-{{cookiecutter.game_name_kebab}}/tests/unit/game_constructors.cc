#include <memory>
#include <utility>

#include "gtest/gtest.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_error}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_ptr}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_result}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

// TODO(TASK-006): delete this test if the default player constructor was deleted.
TEST(GameConstructors, DefaultConstructor) {
  {{cookiecutter.__game_result}} maybe_game = {{cookiecutter.__game_cls}}::Create();
  ASSERT_TRUE(maybe_game.has_value());

  {{cookiecutter.__game_result}} game = std::move(*maybe_game);
  ASSERT_NE(game, nullptr);
}

// TODO(TASK-006): add tests for game constructors.

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}

