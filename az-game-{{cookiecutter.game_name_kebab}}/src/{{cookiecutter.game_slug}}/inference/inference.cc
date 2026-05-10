#include "include/{{cookiecutter.game_slug}}/inference.h"

#include <span>
#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/augmentation.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

std::vector<{{cookiecutter.__game_cls}}>
{{cookiecutter.__infer_aug_cls}}::Augment(
    const {{cookiecutter.__game_cls}}& game) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-INFERENCE-IMPL): typically just delegates to
  // internal::AugmentAll. Override only if inference needs a different
  // (usually smaller) augmentation set than training.
{%- endif %}
  return internal::AugmentAll(game);
}

::az::game::api::Evaluation {{cookiecutter.__infer_aug_cls}}::Interpret(
    const {{cookiecutter.__game_cls}}& original,
    std::span<const {{cookiecutter.__game_cls}}> augmented,
    std::span<const ::az::game::api::Evaluation> evaluations) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-INFERENCE-IMPL): for each (augmented[i], evaluations[i]),
  // map every per-variant action probability back to its original-frame
  // action (typically by composing the inverse symmetry with
  // `original.PolicyIndex`) and accumulate. Average values across
  // variants.
{% else -%}
  // TODO: implementation
{%- endif %}
  return ::az::game::api::Evaluation{0.0f, std::vector<float>{}};
}

}  // namespace az::game::{{cookiecutter.game_slug}}
