#include "include/{{cookiecutter.game_slug}}/serializer.h"

#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "alpha-zero-api/ring_buffer.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

std::vector<float> {{cookiecutter.__serializer_cls}}::SerializeCurrentState(
    const {{cookiecutter.__game_cls}}& game,
    ::az::game::api::RingBufferView<{{cookiecutter.__game_cls}}> history)
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-SERIALIZER-IMPL): encode `game` (and, if non-Markov,
  // `history`) into a fixed-size float vector. Reserve the exact final
  // size before pushing to avoid reallocations. Document the layout in
  // the header.
{% else -%}
  // TODO: implementation
{%- endif %}
  return {};
}

std::vector<float> {{cookiecutter.__serializer_cls}}::SerializePolicyOutput(
    const {{cookiecutter.__game_cls}}& game,
    const ::az::game::api::TrainingTarget& target) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-SERIALIZER-IMPL): encode `target` into a fixed-size float
  // vector. Convention: result[0] = target.z; the rest is the
  // `kPolicySize`-wide policy distribution scattered via
  // `game.PolicyIndex(action)` so invalid actions get zero mass.
{% else -%}
  // TODO: implementation
{%- endif %}
  return {};
}

}  // namespace az::game::{{cookiecutter.game_slug}}
