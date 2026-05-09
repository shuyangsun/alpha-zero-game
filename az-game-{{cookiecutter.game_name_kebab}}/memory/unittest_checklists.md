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
- `SerializeCurrentState` and `SerializePolicyOutput` return fixed-length
  vectors across reachable game states.
- `Deserialize(SerializePolicyOutput(p))` recovers a `PolicyOutput`
  whose `value` and `probabilities` match `p` within numerical
  tolerance.
{% if cookiecutter.augmenter[0] | lower == 'y' -%}
- Inference-time `Augment` returns one entry per
  `{{cookiecutter.__augmentation_enum}}` member; each entry's action
  count equals the input action count.
- Training-time `Augment` returns one tuple per augmentation, with
  `probabilities` permuted to stay aligned with the augmented actions.
{%- endif %}
