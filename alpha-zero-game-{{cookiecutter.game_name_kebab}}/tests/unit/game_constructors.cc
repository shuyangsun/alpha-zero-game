#include <memory>

#include "gtest/gtest.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_interface}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

// TODO(TASK-006): delete this test if the default player constructor was deleted.
TEST(GameConstructors, DefaultConstructor) {
  std::unique_ptr<const {{cookiecutter.__game_interface}}> game = std::make_unique<{{cookiecutter.__game_cls}}>({{ cookiecutter.__player }}{});
  ASSERT_NE(game, nullptr);
}

// TODO(TASK-006): add tests for game constructors.

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}

