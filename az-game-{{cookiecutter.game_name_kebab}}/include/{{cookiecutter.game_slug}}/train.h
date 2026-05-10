#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_TRAIN_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_TRAIN_H_

#include <utility>
#include <vector>

#include "alpha-zero-api/augmenter.h"
#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

/**
 * @brief Training-time augmenter: turn one (game, target) example into N
 * equivalent training tuples by applying every supported augmentation.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-TRAIN-IMPL): tailor this docstring once the augmentation set
 * is finalized. The training augmenter must transform the policy
 * probabilities alongside the board so the network learns
 * symmetry-equivariant policies. `target.z` is preserved unchanged
 * because board symmetries are score-preserving.
{%- endif %}
 */
class {{cookiecutter.__train_aug_cls}}
    : public ::az::game::api::ITrainingAugmenter<{{cookiecutter.__game_cls}}> {
 public:
  {{cookiecutter.__train_aug_cls}}() = default;
  ~{{cookiecutter.__train_aug_cls}}() override = default;

  /**
   * @brief Generate every augmented `(game, target)` training tuple from
   * a single example.
   *
   * Each returned pair contains a {{cookiecutter.__game_cls}} variant and
   * a `TrainingTarget` whose `pi[i]` corresponds to the i-th action
   * written by that variant's `ValidActionsInto(...)`. `target.z` is
   * preserved unchanged.
   *
   * Convention: result includes the identity (typically the first
   * element); callers should not rely on order.
   */
  [[nodiscard]] std::vector<
      std::pair<{{cookiecutter.__game_cls}}, ::az::game::api::TrainingTarget>>
  Augment(const {{cookiecutter.__game_cls}}& game,
          const ::az::game::api::TrainingTarget& target) const noexcept final;
};

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_TRAIN_H_
