#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

{% if cookiecutter.llm[0] | lower == 'y' -%}
// TODO(TASK-UPDATE-GAME-HEADER): change, add, or delete this constructor implementation
// to make the project build successfully, no need to implement constructors yet.
{%- endif %}
{{cookiecutter.__game_cls}}::{{cookiecutter.__game_cls}}(
    const {{cookiecutter.__player}}& player) noexcept
    : cur_player_{player} {}

{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-CONSTRUCTOR-IMPL): add and implement all necessary constructors.
{% else -%}
  // TODO: implementation
{%- endif %}

{{cookiecutter.__result}}<{{cookiecutter.__game_ptr}}>
{{cookiecutter.__game_cls}}::Create(
    {{cookiecutter.__player}} starting_player) noexcept {
  return {{cookiecutter.__game_ptr}}(
      new {{cookiecutter.__game_cls}}(starting_player));
}

{{cookiecutter.__game_ptr}} {{cookiecutter.__game_cls}}::Copy()
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-CONSTRUCTOR-IMPL): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return nullptr;
}

}  // namespace az::game::{{ cookiecutter.game_slug }}
