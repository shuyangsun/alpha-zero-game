#include "include/{{cookiecutter.game_slug}}/inference.h"

#include <cstdint>
#include <span>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/augmentation.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

std::unordered_map<uint8_t, std::tuple<{{cookiecutter.__board}},
                                       {{cookiecutter.__player}},
                                       std::vector<{{cookiecutter.__action}}>>>
{{cookiecutter.__infer_aug_cls}}::Augment(
    const {{cookiecutter.__board}}& board,
    const {{cookiecutter.__player}}& player,
    std::span<const {{cookiecutter.__action}}> actions) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-INFERENCE-IMPL): typically just delegates to
  // internal::AugmentAll. Override only if inference needs a different
  // (usually smaller) augmentation set than training.
{%- endif %}
  return internal::AugmentAll(board, player, actions);
}

::az::game::api::PolicyOutput {{cookiecutter.__infer_aug_cls}}::Interpret(
    const std::unordered_map<
        uint8_t, std::tuple<{{cookiecutter.__board}},
                            {{cookiecutter.__player}},
                            std::vector<{{cookiecutter.__action}}>>>&
        augmented_games,
    const std::unordered_map<uint8_t, ::az::game::api::PolicyOutput>& outputs)
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-INFERENCE-IMPL): for each augmentation key, map every per-
  // variant action probability back to its original-frame action and
  // accumulate. Average values across variants.
{% else -%}
  // TODO: implementation
{%- endif %}
  return ::az::game::api::PolicyOutput{0.0f, std::vector<float>{}};
}

}  // namespace az::game::{{cookiecutter.game_slug}}
