#include "include/{{cookiecutter.game_slug}}/augmentation.h"

#include <vector>

#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}}::internal {

std::vector<{{cookiecutter.__game_cls}}> AugmentAll(
    const {{cookiecutter.__game_cls}}& game) noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-AUGMENTATION-IMPL): return one variant per member of
  // {{cookiecutter.__augmentation_enum}}, in enum order. result[0] must
  // be the identity. Add helpers (rotate, mirror, etc.) above as needed;
  // declare them in the header if other modules need to invert them.
{% else -%}
  // TODO: implementation
{%- endif %}
  std::vector<{{cookiecutter.__game_cls}}> result;
  result.reserve(1);
  result.push_back(game);
  return result;
}

}  // namespace az::game::{{cookiecutter.game_slug}}::internal
