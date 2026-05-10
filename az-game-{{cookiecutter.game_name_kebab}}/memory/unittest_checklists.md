# {{cookiecutter.game_name}} Unittest Checklists

TODO(TASK-REVIEW-GAME-FR-COV): review functional requirements test coverage.

TODO(TASK-UNITTEST-CHECKLIST): use `updating-unittest-checklists` skill.

Beyond the rules-derived items from `game_rules.md`, include FR items that
back the interactive REPL contract from [main_binary.md](./main_binary.md):

- `BoardReadableString` returns a non-empty string and is distinct across
  representative boards (initial, mid-game, terminal).
- `ActionToString` is deterministic and produces a distinct string per
  distinct action in `ValidActions()`.
- `ActionFromString(ActionToString(a))` round-trips for every action `a`
  reachable through legal play.
- `PolicyIndex` is a bijection from `Action` into `[0, kPolicySize)`.
- `ApplyActionInPlace` followed by `UndoLastAction` returns the game to
  its previous state across the deepest MCTS rollout the engine will
  run.
- `SerializeCurrentState` and `SerializePolicyOutput` return fixed-length
  vectors across reachable game states.
- `Deserialize(SerializePolicyOutput(target))` recovers an `Evaluation`
  whose `value` and `probabilities` match `target.z` and `target.pi`
  within numerical tolerance.
{% if cookiecutter.augmenter[0] | lower == 'y' -%}
- Inference-time `Augment` returns one entry per
  `{{cookiecutter.__augmentation_enum}}` member; each variant satisfies
  the same `Game` contract as the input.
- Training-time `Augment` returns one `(game, target)` pair per
  augmentation, with `target.pi` permuted to stay aligned with the
  augmented game's `ValidActions()`.
{%- endif %}
