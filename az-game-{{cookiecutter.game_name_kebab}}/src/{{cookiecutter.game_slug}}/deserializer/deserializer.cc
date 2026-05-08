#include "include/{{cookiecutter.game_slug}}/deserializer.h"

#include <span>
#include <utility>
#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

{{cookiecutter.__result}}<::az::game::api::PolicyOutput>
{{cookiecutter.__deserializer_cls}}::Deserialize(
    const {{cookiecutter.__board}}& board,
    const {{cookiecutter.__player}}& player,
    std::span<const {{cookiecutter.__action}}> actions,
    std::span<const float> output) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-DESERIALIZER-IMPL): map raw network output to a PolicyOutput
  // restricted to `actions`. Validate `output.size()` against the layout
  // produced by {{cookiecutter.__serializer_cls}}::SerializePolicyOutput, and
  // return std::unexpected({{cookiecutter.__game_error}}::...) on mismatch.
{% else -%}
  // TODO: implementation
{%- endif %}
  return std::unexpected({{cookiecutter.__game_error}}::kNotImplemented);
}

}  // namespace az::game::{{cookiecutter.game_slug}}
