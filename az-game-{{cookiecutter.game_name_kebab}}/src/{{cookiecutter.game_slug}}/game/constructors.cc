#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

{% if cookiecutter.llm[0] | lower == 'y' -%}
// TODO(TASK-004): change, add, or delete this constructor implementation if necessary.
{%- endif %}
{{cookiecutter.__game_cls}}::{{cookiecutter.__game_cls}}(
    const {{cookiecutter.__player}}& player) noexcept
    : cur_player_{player} {}

{{cookiecutter.__result}}<{{cookiecutter.__game_ptr}}>
{{cookiecutter.__game_cls}}::Create(
    {{cookiecutter.__player}} starting_player) noexcept {
  return {{cookiecutter.__game_ptr}}(
      new {{cookiecutter.__game_cls}}(starting_player));
}

{{cookiecutter.__game_ptr}} {{cookiecutter.__game_cls}}::Copy()
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return nullptr;
}

}  // namespace az::game::{{ cookiecutter.game_slug }}
