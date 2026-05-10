#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_SERIALIZER_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_SERIALIZER_H_

#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "alpha-zero-api/ring_buffer.h"
#include "alpha-zero-api/serializer.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

/**
 * @brief Serializes {{cookiecutter.game_name}} game state and training
 * target to fixed-size float vectors suitable for neural network
 * input/output.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-SERIALIZER-IMPL): tailor this docstring to be {{cookiecutter.game_name}}
 * specific. Describe the input encoding (channels, shape, normalization)
 * and the output encoding (action layout via `PolicyIndex`, value-slot
 * placement, padding strategy for invalid actions).
{%- endif %}
 *
 * Implements both `::az::game::api::IGameSerializer<{{cookiecutter.__game_cls}}>`
 * and `::az::game::api::IPolicyOutputSerializer<{{cookiecutter.__game_cls}}>`
 * to keep the encoding logic for the neural network input and the training
 * labels together.
 */
class {{cookiecutter.__serializer_cls}}
    : public ::az::game::api::IGameSerializer<{{cookiecutter.__game_cls}}>,
      public ::az::game::api::IPolicyOutputSerializer<{{cookiecutter.__game_cls}}> {
 public:
  {{cookiecutter.__serializer_cls}}() = default;
  ~{{cookiecutter.__serializer_cls}}() override = default;

  /**
   * @brief Serialize the current game state into a fixed-size float
   * vector that is passed as input to the policy/value neural network.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-SERIALIZER-IMPL): tailor this docstring once the input
   * encoding is decided. Common encodings include one-hot per piece type,
   * channels for "to-move" / castling rights / move counters, etc.
   * For non-Markov games, `history` provides the most-recent
   * `kHistoryLookback` past states (index 0 = newest); use them if the
   * input encoding requires temporal context.
{%- endif %}
   *
   * The returned vector MUST be of fixed length across all reachable game
   * states because it is consumed by the neural network as a tensor.
   *
   * @param game Current game state.
   * @param history Engine-owned window over recent past states; size is
   * bounded by `{{cookiecutter.__game_cls}}::kHistoryLookback`. `game`
   * itself is not in the view.
   * @return std::vector<float> Neural network input tensor (flattened).
   */
  [[nodiscard]] std::vector<float> SerializeCurrentState(
      const {{cookiecutter.__game_cls}}& game,
      ::az::game::api::RingBufferView<{{cookiecutter.__game_cls}}> history)
      const noexcept final;

  /**
   * @brief Serialize a `TrainingTarget` (z, π) into a fixed-size float
   * vector suitable for use as a network training target.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-SERIALIZER-IMPL): tailor this docstring once the output
   * encoding is decided. The canonical layout puts `target.z` in slot 0
   * and the `kPolicySize`-wide policy distribution starting at slot 1,
   * scattered via `game.PolicyIndex(action)`.
{%- endif %}
   *
   * The returned vector MUST be of fixed length across all reachable game
   * states. Probability mass for actions not written by
   * `game.ValidActionsInto(...)` should be zero so the network learns
   * the valid-action mask implicitly.
   *
   * `target.pi[i]` corresponds to the i-th legal action — the i-th
   * entry written by `game.ValidActionsInto(...)`. The implementation is
   * responsible for scattering those values into the fixed-size policy
   * slot via `game.PolicyIndex(action)`.
   *
   * @param game Game state the target was produced for.
   * @param target Training target (`z`, `pi`).
   * @return std::vector<float> Neural network output tensor (flattened).
   */
  [[nodiscard]] std::vector<float> SerializePolicyOutput(
      const {{cookiecutter.__game_cls}}& game,
      const ::az::game::api::TrainingTarget& target) const noexcept final;
};

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_SERIALIZER_H_
