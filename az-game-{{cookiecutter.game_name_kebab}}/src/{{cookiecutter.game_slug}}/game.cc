#include "include/{{cookiecutter.game_slug}}/game.h"

#include <cstdint>
#include <expected>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace az::game::{{cookiecutter.game_slug}} {

namespace {

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__action}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__board}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_ptr}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_result}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

// Constants and helper functions here.

}  // namespace

{% if cookiecutter.llm[0] | lower == 'y' -%}
// TODO(TASK-004): change, add, or delete this constructor implementation if necessary.
{%- endif %}
{{cookiecutter.__game_cls}}::{{cookiecutter.__game_cls}}(
    const {{cookiecutter.__player}}& player) noexcept
    : cur_player_{player} {}

{{cookiecutter.__game_result}} {{cookiecutter.__game_cls}}::Create(
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

std::string {{cookiecutter.__game_cls}}::BoardReadableString()
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return "\"BoardReadableString()\" is not implemented!";
}

std::expected<{{cookiecutter.__action}}, std::string>
{{cookiecutter.__game_cls}}::ActionFromString(std::string_view action_str)
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return std::unexpected("\"ActionFromString(...)\" is not implemented!");
}

std::string {{cookiecutter.__game_cls}}::ActionToString(
    const {{cookiecutter.__action}}& action) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-100): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return "\"ActionToString(...)\" is not implemented!";
}

}  // namespace az::game::{{ cookiecutter.game_slug }}
