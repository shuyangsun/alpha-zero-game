#include "include/{{cookiecutter.game_slug}}/train.h"

#include <cstdint>
#include <span>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/augmentation.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

std::vector<std::tuple<{{cookiecutter.__board}}, {{cookiecutter.__player}},
                       std::vector<{{cookiecutter.__action}}>,
                       ::az::game::api::PolicyOutput>>
{{cookiecutter.__train_aug_cls}}::Augment(
    const {{cookiecutter.__board}}& board,
    const {{cookiecutter.__player}}& player,
    std::span<const {{cookiecutter.__action}}> actions,
    ::az::game::api::PolicyOutput&& output) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-TRAIN-IMPL): generate every augmented training example. The
  // policy probabilities must be permuted to match the augmented action
  // ordering so the network learns symmetry-equivariant policies.
{% else -%}
  // TODO: implementation
{%- endif %}
  std::unordered_map<uint8_t,
                     std::tuple<{{cookiecutter.__board}},
                                {{cookiecutter.__player}},
                                std::vector<{{cookiecutter.__action}}>>>
      augmented = internal::AugmentAll(board, player, actions);

  std::vector<std::tuple<{{cookiecutter.__board}}, {{cookiecutter.__player}},
                         std::vector<{{cookiecutter.__action}}>,
                         ::az::game::api::PolicyOutput>>
      result;
  result.reserve(augmented.size());

  for (auto&& [key, game] : augmented) {
    auto& [aug_board, aug_player, aug_actions] = game;
    result.emplace_back(std::move(aug_board), aug_player, std::move(aug_actions),
                        output);
  }

  return result;
}

}  // namespace az::game::{{cookiecutter.game_slug}}
