#include "include/{{cookiecutter.game_slug}}/train.h"

#include <utility>
#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/augmentation.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

std::vector<std::pair<{{cookiecutter.__game_cls}},
                      ::az::game::api::TrainingTarget>>
{{cookiecutter.__train_aug_cls}}::Augment(
    const {{cookiecutter.__game_cls}}& game,
    const ::az::game::api::TrainingTarget& target) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-TRAIN-IMPL): generate every augmented training example.
  // The policy probabilities must be permuted to match the augmented
  // game's `ValidActionsInto(...)` ordering so the network learns
  // symmetry-equivariant policies. `target.z` is preserved unchanged.
{% else -%}
  // TODO: implementation
{%- endif %}
  std::vector<{{cookiecutter.__game_cls}}> augmented = internal::AugmentAll(game);

  std::vector<std::pair<{{cookiecutter.__game_cls}},
                        ::az::game::api::TrainingTarget>>
      result;
  result.reserve(augmented.size());

  for (auto&& aug_game : augmented) {
{% if cookiecutter.llm[0] | lower == 'y' -%}
    // TODO(TASK-TRAIN-IMPL): permute `target.pi` so probabilities stay
    // aligned with the actions written by `aug_game.ValidActionsInto(...)`.
    // Copying `target` unchanged (as below) trains the network to be
    // augmentation-invariant instead of equivariant — wrong, but lets the
    // placeholder compile.
{%- endif %}
    result.emplace_back(std::move(aug_game), target);
  }

  return result;
}

}  // namespace az::game::{{cookiecutter.game_slug}}
