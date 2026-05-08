#include "include/{{cookiecutter.game_slug}}/augmentation.h"

#include <cstdint>
#include <span>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}}::internal {

std::unordered_map<uint8_t, std::tuple<{{cookiecutter.__board}},
                                       {{cookiecutter.__player}},
                                       std::vector<{{cookiecutter.__action}}>>>
AugmentAll(const {{cookiecutter.__board}}& board,
           const {{cookiecutter.__player}}& player,
           std::span<const {{cookiecutter.__action}}> actions) noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-AUGMENTATION-IMPL): apply every member of
  // {{cookiecutter.__augmentation_enum}} to (board, player, actions) and
  // populate the result map. Add helpers (rotate, mirror, etc.) above as
  // needed; declare them in the header if other modules need to invert them.
{% else -%}
  // TODO: implementation
{%- endif %}
  using enum {{cookiecutter.__augmentation_enum}};
  std::unordered_map<uint8_t,
                     std::tuple<{{cookiecutter.__board}},
                                {{cookiecutter.__player}},
                                std::vector<{{cookiecutter.__action}}>>>
      result;
  result.emplace(
      static_cast<uint8_t>(kOriginal),
      std::make_tuple(board, player,
                      std::vector<{{cookiecutter.__action}}>(
                          actions.begin(), actions.end())));
  return result;
}

}  // namespace az::game::{{cookiecutter.game_slug}}::internal
