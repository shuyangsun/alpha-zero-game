#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_

#include <array>
#include <cstdint>

#include "alpha-zero-api/game.h"

namespace alphazero::game::{{cookiecutter.game_slug}} {

using {{cookiecutter.__board}} = std::array<std::array<int8_t, 3>, 3>;  // TODO: change type
using {{cookiecutter.__action}} = int;                                  // TODO: change type
using {{cookiecutter.__player}} = bool;                                 // TODO: change type
using {{cookiecutter.__game_interface}} = ::alphazero::game::api::IGame<{{cookiecutter.__board}}, {{cookiecutter.__action}}, {{cookiecutter.__player}}>;

class {{cookiecutter.__game_cls}}: public {{cookiecutter.__game_interface}} {
public:
  {{cookiecutter.__game_cls}}() = default;
  ~{{cookiecutter.__game_cls}}() override = default;
};

} // namespace alphazero::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_

