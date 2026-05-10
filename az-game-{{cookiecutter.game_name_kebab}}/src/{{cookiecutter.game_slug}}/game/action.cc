#include "include/{{cookiecutter.game_slug}}/game.h"

#include <array>
#include <cstddef>

namespace az::game::{{cookiecutter.game_slug}} {

std::size_t {{cookiecutter.__game_cls}}::ValidActionsInto(
    std::array<{{cookiecutter.__action}},
               {{cookiecutter.__game_cls}}::kMaxLegalActions>& out)
    const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-ACTION-IMPL): implementation. Write each legal action
  // into `out[0..count)` and return `count`. Must be deterministic in
  // the game state, allocation-free, and return `0` iff `IsOver()`
  // returns `true`. Callers ignore entries at indices `>= count`, so do
  // not zero the rest of the buffer.
{% else -%}
  // TODO: implementation
{%- endif %}
  (void)out;
  return 0;
}

std::size_t {{cookiecutter.__game_cls}}::PolicyIndex(
    const {{cookiecutter.__action}}& action) const noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-ACTION-IMPL): bijection from action to slot in
  // `[0, kPolicySize)`.
{% else -%}
  // TODO: implementation
{%- endif %}
  return 0;
}

void {{cookiecutter.__game_cls}}::ApplyActionInPlace(
    const {{cookiecutter.__action}}& action) noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-ACTION-IMPL): apply `action` to this state in place.
  // Update `board_`, `cur_player_`, and any history needed by
  // `UndoLastAction`. Must be allocation-free.
{% else -%}
  // TODO: implementation
{%- endif %}
  last_player_ = cur_player_;
  last_action_ = action;
  ++round_;
}

void {{cookiecutter.__game_cls}}::UndoLastAction() noexcept {
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-GAME-ACTION-IMPL): reverse the most recent
  // `ApplyActionInPlace`. No-op if there is nothing to undo. Must be
  // allocation-free. The placeholder below only supports a single level of
  // undo; extend the private state if MCTS will need deeper rollouts.
{% else -%}
  // TODO: implementation
{%- endif %}
  if (!last_action_.has_value()) {
    return;
  }
  cur_player_ = last_player_.value_or(cur_player_);
  last_action_ = std::nullopt;
  last_player_ = std::nullopt;
  if (round_ > 0) {
    --round_;
  }
}

}  // namespace az::game::{{ cookiecutter.game_slug }}
