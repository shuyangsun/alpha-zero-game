#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_AUGMENTATION_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_AUGMENTATION_H_

#include <cstdint>
#include <span>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}}::internal {

/**
 * @brief Identifiers for each augmented variant of a {{cookiecutter.game_name}}
 * game state.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-AUGMENTATION-IMPL): enumerate every augmentation that preserves
 * {{cookiecutter.game_name}} game equivalence (e.g., rotations, mirrors, color
 * swaps). For games with no useful symmetry, keep just `kOriginal` and the
 * augmenters will degenerate into identity transforms.
{%- endif %}
 */
enum class {{cookiecutter.__augmentation_enum}} : uint8_t {
  kOriginal = 0,
};

/**
 * @brief Apply every supported augmentation to (board, player, actions) and
 * return a map keyed by the augmentation identifier.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-AUGMENTATION-IMPL): implement the augmentation logic. Each entry
 * in the returned map must include the same number of valid actions as the
 * input span; the action ordering inside each variant is implementation
 * defined but must be consistent with what `Interpret` in
 * {{cookiecutter.__infer_aug_cls}} expects.
{%- endif %}
 *
 * @param board Original board state.
 * @param player Original current player.
 * @param actions Valid actions for the original game state.
 * @return Map from augmentation key to (augmented board, augmented player,
 * augmented actions).
 */
[[nodiscard]] std::unordered_map<
    uint8_t, std::tuple<{{cookiecutter.__board}}, {{cookiecutter.__player}},
                        std::vector<{{cookiecutter.__action}}>>>
AugmentAll(const {{cookiecutter.__board}}& board,
           const {{cookiecutter.__player}}& player,
           std::span<const {{cookiecutter.__action}}> actions) noexcept;

}  // namespace az::game::{{cookiecutter.game_slug}}::internal

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_AUGMENTATION_H_
