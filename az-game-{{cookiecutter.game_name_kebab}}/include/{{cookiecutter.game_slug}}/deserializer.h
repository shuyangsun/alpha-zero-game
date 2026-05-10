#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_DESERIALIZER_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_DESERIALIZER_H_

#include <span>

#include "alpha-zero-api/deserializer.h"
#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

/**
 * @brief Deserializes the raw float output from the policy/value neural
 * network into an `::az::game::api::Evaluation`.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-DESERIALIZER-IMPL): tailor this docstring to describe how the
 * neural network output is laid out and how it is mapped back onto valid
 * actions for {{cookiecutter.game_name}}.
{%- endif %}
 *
 * The deserializer must mirror the layout produced by
 * `{{cookiecutter.__serializer_cls}}::SerializePolicyOutput`. The
 * `Evaluation::probabilities` vector returned must have the same length
 * as the count returned by `game.ValidActionsInto(...)` and align 1:1
 * with the actions written into that buffer. Implementations typically
 * gather the masked subset of policy slots via `game.PolicyIndex(action)`.
 */
class {{cookiecutter.__deserializer_cls}}
    : public ::az::game::api::IPolicyOutputDeserializer<
          {{cookiecutter.__game_cls}}, {{cookiecutter.__game_error}}> {
 public:
  {{cookiecutter.__deserializer_cls}}() = default;
  ~{{cookiecutter.__deserializer_cls}}() override = default;

  /**
   * @brief Convert raw neural network output into an `Evaluation`
   * restricted to the actions returned by `game.ValidActionsInto(...)`.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-DESERIALIZER-IMPL): document the expected output size, the
   * action -> index mapping (typically via `game.PolicyIndex`), and the
   * renormalization strategy (e.g., softmax over masked logits).
{%- endif %}
   *
   * @param game Game state used to produce the network input.
   * @param output Raw network output tensor (flat). Callers must
   * up-convert FP16/BF16 outputs to FP32 before invoking the
   * deserializer.
   * @return {{cookiecutter.__result}}<::az::game::api::Evaluation>
   *         `Evaluation` on success, error on malformed input.
   */
  [[nodiscard]] {{cookiecutter.__result}}<::az::game::api::Evaluation>
  Deserialize(const {{cookiecutter.__game_cls}}& game,
              std::span<const float> output) const noexcept final;
};

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_DESERIALIZER_H_
