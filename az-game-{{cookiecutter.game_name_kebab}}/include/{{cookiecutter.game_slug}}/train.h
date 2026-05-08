#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_TRAIN_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_TRAIN_H_

#include <span>
#include <tuple>
#include <vector>

#include "alpha-zero-api/augmenter.h"
#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

/**
 * @brief Training-time augmenter: turn one (state, policy) example into N
 * equivalent training examples by applying every supported augmentation.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-TRAIN-IMPL): tailor this docstring once the augmentation set is
 * finalized. The training augmenter must transform the policy probabilities
 * alongside the board so the network learns symmetry-equivariant policies.
{%- endif %}
 */
class {{cookiecutter.__train_aug_cls}}
    : public ::az::game::api::ITrainingAugmenter<{{cookiecutter.__board}},
                                                 {{cookiecutter.__action}},
                                                 {{cookiecutter.__player}}> {
 public:
  {{cookiecutter.__train_aug_cls}}() = default;
  ~{{cookiecutter.__train_aug_cls}}() override = default;

  /**
   * @brief Generate every augmented training tuple from a single example.
   *
   * Each returned tuple contains a board, the player to move, the valid
   * actions in the augmented frame, and the policy output rotated to match.
   * The library will pass each tuple through the serializer to produce a
   * training pair.
   *
   * @param board Original board state.
   * @param player Original current player.
   * @param actions Valid actions for the original game state.
   * @param output Policy output for the original game state (consumed).
   * @return Vector of (board, player, actions, policy) tuples.
   */
  [[nodiscard]] std::vector<
      std::tuple<{{cookiecutter.__board}}, {{cookiecutter.__player}},
                 std::vector<{{cookiecutter.__action}}>,
                 ::az::game::api::PolicyOutput>>
  Augment(const {{cookiecutter.__board}}& board,
          const {{cookiecutter.__player}}& player,
          std::span<const {{cookiecutter.__action}}> actions,
          ::az::game::api::PolicyOutput&& output) const noexcept final;
};

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_TRAIN_H_
