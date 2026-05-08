#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_INFERENCE_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_INFERENCE_H_

#include <cstdint>
#include <span>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "alpha-zero-api/augmenter.h"
#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

/**
 * @brief Inference-time augmenter: expand one game state into N equivalent
 * states, then aggregate the per-variant policy outputs back into a single
 * PolicyOutput for the original state.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-INFERENCE-IMPL): tailor this docstring once the augmentation set
 * is finalized. Document how variant probabilities are rotated/mirrored back
 * to the original action space, and how multiple variant values are combined
 * (mean is the typical choice).
{%- endif %}
 */
class {{cookiecutter.__infer_aug_cls}}
    : public ::az::game::api::IInferenceAugmenter<{{cookiecutter.__board}},
                                                  {{cookiecutter.__action}},
                                                  {{cookiecutter.__player}}> {
 public:
  {{cookiecutter.__infer_aug_cls}}() = default;
  ~{{cookiecutter.__infer_aug_cls}}() override = default;

  /**
   * @brief Expand the input game state into all augmented variants.
   *
   * Keys must match the keys used in `Interpret`. Conventionally these are
   * cast values of the {{cookiecutter.__augmentation_enum}} enum.
   *
   * @param board Original board state.
   * @param player Original current player.
   * @param actions Valid actions for the original game state.
   * @return Map from augmentation key to (board, player, actions).
   */
  [[nodiscard]] std::unordered_map<
      uint8_t, std::tuple<{{cookiecutter.__board}}, {{cookiecutter.__player}},
                          std::vector<{{cookiecutter.__action}}>>>
  Augment(const {{cookiecutter.__board}}& board,
          const {{cookiecutter.__player}}& player,
          std::span<const {{cookiecutter.__action}}> actions)
      const noexcept final;

  /**
   * @brief Combine per-variant policy outputs into a single PolicyOutput for
   * the original game state.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-INFERENCE-IMPL): document the inverse mapping from each variant
   * action back to the original action, and the aggregation strategy
   * (mean / max / weighted, etc.).
{%- endif %}
   *
   * @param augmented_games The map returned by `Augment`.
   * @param outputs Per-variant policy outputs, keyed identically.
   * @return Aggregated PolicyOutput on the original action space.
   */
  [[nodiscard]] ::az::game::api::PolicyOutput Interpret(
      const std::unordered_map<
          uint8_t, std::tuple<{{cookiecutter.__board}},
                              {{cookiecutter.__player}},
                              std::vector<{{cookiecutter.__action}}>>>&
          augmented_games,
      const std::unordered_map<uint8_t, ::az::game::api::PolicyOutput>&
          outputs) const noexcept final;
};

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_INFERENCE_H_
