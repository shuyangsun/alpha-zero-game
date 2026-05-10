#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_INFERENCE_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_INFERENCE_H_

#include <span>
#include <vector>

#include "alpha-zero-api/augmenter.h"
#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

/**
 * @brief Inference-time augmenter: expand one game state into N
 * equivalent states, then aggregate the per-variant `Evaluation`s back
 * into a single `Evaluation` for the original state.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-INFERENCE-IMPL): tailor this docstring once the augmentation
 * set is finalized. Document how variant probabilities are
 * rotated/mirrored back to the original action space, and how multiple
 * variant values are combined (mean is the typical choice).
{%- endif %}
 */
class {{cookiecutter.__infer_aug_cls}}
    : public ::az::game::api::IInferenceAugmenter<{{cookiecutter.__game_cls}}> {
 public:
  {{cookiecutter.__infer_aug_cls}}() = default;
  ~{{cookiecutter.__infer_aug_cls}}() override = default;

  /**
   * @brief Expand the input game state into all augmented variants.
   *
   * Convention: `result[0]` is the identity (`game` itself), so a game
   * with no useful symmetry can return a one-element vector and
   * `Interpret` becomes effectively the identity. The order matches the
   * `{{cookiecutter.__augmentation_enum}}` enum.
   */
  [[nodiscard]] std::vector<{{cookiecutter.__game_cls}}> Augment(
      const {{cookiecutter.__game_cls}}& game) const noexcept final;

  /**
   * @brief Combine per-variant evaluations into a single `Evaluation`
   * for the original game state.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-INFERENCE-IMPL): document the inverse mapping from each
   * variant action back to the original action, and the aggregation
   * strategy (mean / max / weighted, etc.).
{%- endif %}
   *
   * `augmented` and `evaluations` are aligned: `evaluations[i]`
   * corresponds to `augmented[i]`. The returned `Evaluation`'s
   * probabilities must align 1:1 with the actions returned by
   * `original.ValidActionsInto(...)`; the implementation is responsible
   * for inverting whatever symmetry it applied.
   */
  [[nodiscard]] ::az::game::api::Evaluation Interpret(
      const {{cookiecutter.__game_cls}}& original,
      std::span<const {{cookiecutter.__game_cls}}> augmented,
      std::span<const ::az::game::api::Evaluation> evaluations)
      const noexcept final;
};

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_INFERENCE_H_
