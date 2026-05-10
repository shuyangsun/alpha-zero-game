#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_AUGMENTATION_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_AUGMENTATION_H_

#include <cstdint>
#include <vector>

#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}}::internal {

/**
 * @brief Identifiers for each augmented variant of a {{cookiecutter.game_name}}
 * game state.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-AUGMENTATION-IMPL): enumerate every augmentation that
 * preserves {{cookiecutter.game_name}} game equivalence (e.g., rotations,
 * mirrors, color swaps). For games with no useful symmetry, keep just
 * `kOriginal` and the augmenters will degenerate into identity
 * transforms.
{%- endif %}
 */
enum class {{cookiecutter.__augmentation_enum}} : uint8_t {
  kOriginal = 0,
};

/**
 * @brief Apply every supported augmentation to `game` and return the
 * resulting variants.
{% if cookiecutter.llm[0] | lower == 'y' -%}
 *
 * TODO(TASK-AUGMENTATION-IMPL): implement the augmentation logic. The
 * returned vector must have one entry per member of
 * `{{cookiecutter.__augmentation_enum}}`, in enum order, so the index of
 * each variant doubles as its augmentation key. `result[0]` must be the
 * identity (`game` itself).
{%- endif %}
 *
 * Each returned `{{cookiecutter.__game_cls}}` must satisfy the same `Game`
 * contract as the input — including `ValidActions()` size and
 * deterministic ordering — so per-variant network outputs can be
 * inverse-mapped back to the original action space.
 *
 * @param game Original game state.
 * @return Augmented variants in enum order.
 */
[[nodiscard]] std::vector<{{cookiecutter.__game_cls}}> AugmentAll(
    const {{cookiecutter.__game_cls}}& game) noexcept;

}  // namespace az::game::{{cookiecutter.game_slug}}::internal

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_AUGMENTATION_H_
