#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

std::vector<{{cookiecutter.__action}}>
{{cookiecutter.__game_cls}}::ValidActions() const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return {};
}

{{cookiecutter.__game_ptr}} {{cookiecutter.__game_cls}}::GameAfterAction(
    const {{cookiecutter.__action}}& action) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return nullptr;
}

}  // namespace az::game::{{ cookiecutter.game_slug }}
