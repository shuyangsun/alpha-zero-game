#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

std::string {{cookiecutter.__game_cls}}::BoardReadableString()
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-STR-IMPL): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return "\"BoardReadableString()\" is not implemented!";
}

{{cookiecutter.__result}}<{{cookiecutter.__action}}>
{{cookiecutter.__game_cls}}::ActionFromString(std::string_view action_str)
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-STR-IMPL): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return std::unexpected({{cookiecutter.__game_error}}::kNotImplemented);
}

std::string {{cookiecutter.__game_cls}}::ActionToString(
    const {{cookiecutter.__action}}& action) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-STR-IMPL): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return "\"ActionToString(...)\" is not implemented!";
}

}  // namespace az::game::{{ cookiecutter.game_slug }}
