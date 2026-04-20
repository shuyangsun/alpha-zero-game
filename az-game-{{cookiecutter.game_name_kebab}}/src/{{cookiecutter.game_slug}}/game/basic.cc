#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

const {{cookiecutter.__board}}& {{cookiecutter.__game_cls}}::GetBoard()
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-BASIC-IMPL): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
    const noexcept {
  return board_;
}

uint32_t {{cookiecutter.__game_cls}}::CurrentRound() const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-BASIC-IMPL): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return round_;
}

{{cookiecutter.__player}} {{cookiecutter.__game_cls}}::CurrentPlayer()
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-BASIC-IMPL): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return cur_player_;
}

std::optional<{{cookiecutter.__player}}>
{{cookiecutter.__game_cls}}::LastPlayer() const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-BASIC-IMPL): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return {};
}

std::optional<{{cookiecutter.__action}}>
{{cookiecutter.__game_cls}}::LastAction() const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-BASIC-IMPL): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return last_action_;
}

}  // namespace az::game::{{ cookiecutter.game_slug }}
