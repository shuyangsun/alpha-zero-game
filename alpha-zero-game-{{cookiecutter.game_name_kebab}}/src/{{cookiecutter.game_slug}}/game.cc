#include "include/{{cookiecutter.game_slug}}/game.h"

#include <cstdint>
#include <expected>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace alphazero::game::{{cookiecutter.game_slug}} {

namespace {

// Using statements, constexpr, helper functions here.

}  // namespace

{% if cookiecutter.llm[0] | lower == 'y' -%}
// TODO(TASK-002): change, add, or delete this constructor implementation if necessary.
{%- endif %}
{{cookiecutter.__game_cls}}::{{cookiecutter.__game_cls}}(const {{cookiecutter.__player}}& player)
    : cur_player_{player} {}

std::unique_ptr<const {{cookiecutter.__game_interface}}> {{cookiecutter.__game_cls}}::Copy() const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return nullptr;
}

const {{cookiecutter.__board}}& {{cookiecutter.__game_cls}}::GetBoard() const {
  return board_;
}

uint32_t {{cookiecutter.__game_cls}}::CurrentRound() const {
  return round_;
}

{{cookiecutter.__player}} {{cookiecutter.__game_cls}}::CurrentPlayer() const {
  return cur_player_;
}

std::optional<{{cookiecutter.__player}}> {{cookiecutter.__game_cls}}::LastPlayer() const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return {};
}

std::optional<{{cookiecutter.__action}}> {{cookiecutter.__game_cls}}::LastAction() const {
  return last_action_;
}

{{cookiecutter.__board}} {{cookiecutter.__game_cls}}::CanonicalBoard() const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return board_;
}

bool {{cookiecutter.__game_cls}}::IsOver() const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return false;
}

float {{cookiecutter.__game_cls}}::GetScore(const {{cookiecutter.__player}}& player) const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return 0.0f;
}

std::vector<{{cookiecutter.__action}}> {{cookiecutter.__game_cls}}::ValidActions() const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return {};
}

std::unique_ptr<const {{cookiecutter.__game_interface}}> {{cookiecutter.__game_cls}}::GameAfterAction(
      const {{cookiecutter.__action}}& action) const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return nullptr;
}

std::string {{cookiecutter.__game_cls}}::BoardReadableString() const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return "\"BoardReadableString()\" is not implemented!";
}

std::expected<{{cookiecutter.__action}}, std::string> {{cookiecutter.__game_cls}}::ActionFromString(
      std::string_view action_str) const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return std::unexpected("\"ActionFromString(...)\" is not implemented!");
}

std::string {{cookiecutter.__game_cls}}::ActionToString(const {{cookiecutter.__action}}& action) const {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-005): implementation
{% else -%}
  // TODO: implementation
{%- endif %}
  return "\"ActionToString(...)\" is not implemented!";
}

}  // namespace alphazero::game::{{ cookiecutter.game_slug }}

