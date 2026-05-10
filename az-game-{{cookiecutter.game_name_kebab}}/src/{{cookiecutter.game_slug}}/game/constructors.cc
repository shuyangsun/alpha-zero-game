#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

{% if cookiecutter.llm[0] | lower == 'y' -%}
// TODO(TASK-GAME-CONSTRUCTOR-IMPL): change, add, or delete constructor
// implementations to match your game's design.
{% else -%}
// TODO: implementation
{%- endif %}
{{cookiecutter.__game_cls}}::{{cookiecutter.__game_cls}}(
    const {{cookiecutter.__player}}& starting_player) noexcept
    : cur_player_{starting_player} {}

}  // namespace az::game::{{ cookiecutter.game_slug }}
