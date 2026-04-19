#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

#include "include/{{cookiecutter.game_slug}}/game.h"

namespace {

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_error}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_ptr}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_result}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

} // namespace

int main() {
  std::cout << "Hello, {{ cookiecutter.game_name }}!" << std::endl;
  {{cookiecutter.__game_result}} maybe_game = {{cookiecutter.__game_cls}}::Create();
  if (!maybe_game.has_value()) {
    std::cerr << "Error creating game: "
              << static_cast<std::underlying_type_t<{{cookiecutter.__game_error}}>>(
                     maybe_game.error())
              << std::endl;
    return 1;
  }

  {{cookiecutter.__game_ptr}} game = std::move(*maybe_game);
  std::cout << game->BoardReadableString() << std::endl;
  return 0;
}

