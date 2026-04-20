#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

{{cookiecutter.__board}} {{cookiecutter.__game_cls}}::CanonicalBoard()
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return board_;
}

bool {{cookiecutter.__game_cls}}::IsOver() const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return false;
}

float {{cookiecutter.__game_cls}}::GetScore(
    const {{cookiecutter.__player}}& player) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return 0.0f;
}

}  // namespace az::game::{{ cookiecutter.game_slug }}
