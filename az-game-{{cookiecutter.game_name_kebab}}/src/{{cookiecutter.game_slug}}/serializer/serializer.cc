#include "include/{{cookiecutter.game_slug}}/serializer.h"

#include <span>
#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

std::vector<float> {{cookiecutter.__serializer_cls}}::SerializeCurrentState(
    const {{cookiecutter.__board}}& board,
    const {{cookiecutter.__player}}& player,
    std::span<const {{cookiecutter.__action}}> actions) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-SERIALIZER-IMPL): encode (board, player, actions) into a
  // fixed-size float vector. Reserve the exact final size before pushing to
  // avoid reallocations. Document the layout in the header.
{% else -%}
  // TODO: implementation
{%- endif %}
  return {};
}

std::vector<float> {{cookiecutter.__serializer_cls}}::SerializePolicyOutput(
    const {{cookiecutter.__board}}& board,
    const {{cookiecutter.__player}}& player,
    std::span<const {{cookiecutter.__action}}> actions,
    const ::az::game::api::PolicyOutput& output) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-SERIALIZER-IMPL): encode `output` into a fixed-size float
  // vector. Convention: result[0] = output.value; the rest is the policy
  // distribution laid out so invalid actions get zero mass.
{% else -%}
  // TODO: implementation
{%- endif %}
  return {};
}

}  // namespace az::game::{{cookiecutter.game_slug}}
