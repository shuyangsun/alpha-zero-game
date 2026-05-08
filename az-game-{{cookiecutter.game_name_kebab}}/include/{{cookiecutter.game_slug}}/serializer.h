#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_SERIALIZER_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_SERIALIZER_H_

#include <span>
#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "alpha-zero-api/serializer.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

/**
 * @brief Serializes {{cookiecutter.game_name}} game state and policy output to
 * fixed-size float vectors suitable for neural network input/output.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-SERIALIZER-IMPL): tailor this docstring to be {{cookiecutter.game_name}}
 * specific. Describe the input encoding (channels, shape, normalization) and
 * the output encoding (action layout, padding strategy for invalid actions).
{%- endif %}
 *
 * Implements both ::az::game::api::IGameSerializer and
 * ::az::game::api::IPolicyOutputSerializer to keep the encoding logic for the
 * neural network input and the training labels together.
 */
class {{cookiecutter.__serializer_cls}}
    : public ::az::game::api::IGameSerializer<{{cookiecutter.__board}},
                                              {{cookiecutter.__action}},
                                              {{cookiecutter.__player}}>,
      public ::az::game::api::IPolicyOutputSerializer<{{cookiecutter.__board}},
                                                      {{cookiecutter.__action}},
                                                      {{cookiecutter.__player}}> {
 public:
  {{cookiecutter.__serializer_cls}}() = default;
  ~{{cookiecutter.__serializer_cls}}() override = default;

  /**
   * @brief Serialize the current game state into a fixed-size float vector
   * that is passed as input to the policy/value neural network.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-SERIALIZER-IMPL): tailor this docstring once the input encoding
   * is decided. Common encodings include one-hot per piece type, channels for
   * "to-move" / castling rights / move counters, etc.
{%- endif %}
   *
   * The returned vector MUST be of fixed length across all reachable game
   * states because it is consumed by the neural network as a tensor.
   *
   * @param board Current board state.
   * @param player Current player.
   * @param actions Valid actions for the current player.
   * @return std::vector<float> Neural network input tensor (flattened).
   */
  [[nodiscard]] std::vector<float> SerializeCurrentState(
      const {{cookiecutter.__board}}& board,
      const {{cookiecutter.__player}}& player,
      std::span<const {{cookiecutter.__action}}> actions) const noexcept final;

  /**
   * @brief Serialize a policy output (value + per-action probabilities) into
   * a fixed-size float vector suitable for use as a training target.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-SERIALIZER-IMPL): tailor this docstring once the output encoding
   * is decided. The first element is conventionally the value; the rest are
   * action probabilities laid out so that invalid actions get zero mass.
{%- endif %}
   *
   * The returned vector MUST be of fixed length across all reachable game
   * states. Probability mass for actions that are not in `actions` should be
   * zero so the network can learn the valid-action mask implicitly.
   *
   * @param board Current board state.
   * @param player Current player.
   * @param actions Valid actions for the current player (parallel to
   *                `output.probabilities`).
   * @param output Policy output to serialize.
   * @return std::vector<float> Neural network output tensor (flattened).
   */
  [[nodiscard]] std::vector<float> SerializePolicyOutput(
      const {{cookiecutter.__board}}& board,
      const {{cookiecutter.__player}}& player,
      std::span<const {{cookiecutter.__action}}> actions,
      const ::az::game::api::PolicyOutput& output) const noexcept final;
};

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_SERIALIZER_H_
