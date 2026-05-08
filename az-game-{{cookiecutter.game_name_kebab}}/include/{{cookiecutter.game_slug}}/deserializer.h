#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_DESERIALIZER_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_DESERIALIZER_H_

#include <span>

#include "alpha-zero-api/deserializer.h"
#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

/**
 * @brief Deserializes the raw float output from the policy/value neural
 * network into a {{cookiecutter.game_name}} ::az::game::api::PolicyOutput.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-DESERIALIZER-IMPL): tailor this docstring to describe how the
 * neural network output is laid out and how it is mapped back onto valid
 * actions for {{cookiecutter.game_name}}.
{%- endif %}
 *
 * The deserializer must mirror the layout produced by
 * {{cookiecutter.__serializer_cls}}::SerializePolicyOutput. The probability
 * vector returned in the PolicyOutput must have the same length as the
 * `actions` span passed to `Deserialize`. The library asserts on this.
 */
class {{cookiecutter.__deserializer_cls}}
    : public ::az::game::api::IPolicyOutputDeserializer<{{cookiecutter.__board}},
                                                        {{cookiecutter.__action}},
                                                        {{cookiecutter.__player}},
                                                        {{cookiecutter.__game_error}}> {
 public:
  {{cookiecutter.__deserializer_cls}}() = default;
  ~{{cookiecutter.__deserializer_cls}}() override = default;

  /**
   * @brief Convert raw neural network output into a PolicyOutput restricted
   * to the given valid actions.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-DESERIALIZER-IMPL): document the expected output size, the
   * action -> index mapping, and the renormalization strategy (e.g., softmax
   * over masked logits).
{%- endif %}
   *
   * @param board Board state used to produce the network input.
   * @param player Current player.
   * @param actions Valid actions; the returned probabilities vector must be
   * parallel to this.
   * @param output Raw network output tensor (flat).
   * @return {{cookiecutter.__result}}<::az::game::api::PolicyOutput>
   *         PolicyOutput on success, error on malformed output.
   */
  [[nodiscard]] {{cookiecutter.__result}}<::az::game::api::PolicyOutput>
  Deserialize(const {{cookiecutter.__board}}& board,
              const {{cookiecutter.__player}}& player,
              std::span<const {{cookiecutter.__action}}> actions,
              std::span<const float> output) const noexcept final;
};

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_DESERIALIZER_H_
