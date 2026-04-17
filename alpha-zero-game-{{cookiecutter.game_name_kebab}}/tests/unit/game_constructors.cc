#include <memory>

#include "gtest/gtest.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace alphazero::game::{{cookiecutter.game_slug}} {
namespace {

using ::alphazero::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_interface}};
using ::alphazero::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

TEST(GameConstructors, MakeUniqueAndCastToInterface) {
  std::unique_ptr<const {{cookiecutter.__game_interface}}> game = std::make_unique<{{cookiecutter.__game_cls}}>({{ cookiecutter.__player }}{});
  ASSERT_NE(game, nullptr);
}

}  // namespace
}  // namespace alphazero::game::{{cookiecutter.game_slug}}

