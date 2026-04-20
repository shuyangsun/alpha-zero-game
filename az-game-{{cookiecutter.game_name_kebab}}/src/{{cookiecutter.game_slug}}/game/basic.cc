#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

const {{cookiecutter.__board}}& {{cookiecutter.__game_cls}}::GetBoard()
    const noexcept {
  return board_;
}

uint32_t {{cookiecutter.__game_cls}}::CurrentRound() const noexcept {
  return round_;
}

{{cookiecutter.__player}} {{cookiecutter.__game_cls}}::CurrentPlayer()
    const noexcept {
  return cur_player_;
}

std::optional<{{cookiecutter.__player}}>
{{cookiecutter.__game_cls}}::LastPlayer() const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return {};
}

std::optional<{{cookiecutter.__action}}>
{{cookiecutter.__game_cls}}::LastAction() const noexcept {
  return last_action_;
}

}  // namespace az::game::{{ cookiecutter.game_slug }}
