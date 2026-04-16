#include <iostream>
#include <memory>

#include "include/{{cookiecutter.game_slug}}/game.h"

namespace {

using ::alphazero::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_interface}};
using ::alphazero::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::alphazero::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

} // namespace

int main() {
  std::cout << "Hello, {{ cookiecutter.game_name }}!" << std::endl;
  std::unique_ptr<const {{cookiecutter.__game_interface}}> game = std::make_unique<{{cookiecutter.__game_cls}}>({{cookiecutter.__player}}{});
  std::cout << game->BoardReadableString() << std::endl;
  return 0;
}
