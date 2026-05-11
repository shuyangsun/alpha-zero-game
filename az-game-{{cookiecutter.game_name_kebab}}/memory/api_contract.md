# AlphaZero API Contract

A condensed reference to the upstream
[shuyangsun/alpha-zero-api](https://github.com/shuyangsun/alpha-zero-api)
contract this project implements. Read this once before working on
[game_design.md](./game_design.md) or any `*-IMPL` task — almost every
implementation decision is shaped by something below.

The full headers live under `src/include/alpha-zero-api/` in the upstream
repo (and in `build/debug/_deps/alphazeroapi-src/...` once the project
has been built — see the `finding-alpha-zero-api` skill).

## The `Game` concept

`{{cookiecutter.__game_cls}}` must satisfy `::az::game::api::Game`.
Failure is a hard compile error from the `static_assert` at the bottom
of [game.h](../include/{{cookiecutter.game_slug}}/game.h).

The concept is value-semantic and statically dispatched — no virtual
methods, no `unique_ptr` factory, no `IGame<...>` base class. The MCTS
engine is templated on `{{cookiecutter.__game_cls}}` and stores
instances by value.

### Required associated types

- `board_t` / `action_t` / `player_t` / `error_t`
- `action_t` must satisfy `std::equality_comparable`. The MCTS engine,
  the REPL, and tests rely on `operator==` to match an action against
  the buffer written by `ValidActionsInto(...)`. Arithmetic types,
  `enum class`, and `std::array` of equality-comparable elements get
  this for free; custom struct/class action types must define
  `operator==` explicitly (a defaulted `friend` is usually correct).

### Required `static constexpr` members

- `kHistoryLookback : std::size_t` — past states the serializer needs.
  Markov games declare 0. See [history_lookback.md](./history_lookback.md).
- `kPolicySize : std::size_t` — cardinality of the full action space,
  ignoring legality. Equals the network's policy-head width for a
  dense head.
- `kMaxLegalActions : std::size_t` — per-state upper bound on the
  number of legal actions; sizes the caller-owned buffer passed to
  `ValidActionsInto`. Must satisfy `kMaxLegalActions <= kPolicySize`.
  Dense policy heads set `kMaxLegalActions = kPolicySize`. Compact
  heads set this to a tight per-state ceiling — see the
  [designing-serialization](../.agents/skills/designing-serialization/SKILL.md)
  skill for when to choose compact.
- `kMaxRounds : std::optional<uint32_t>` — self-play hard cap. If set,
  `IsOver()` must return `true` once `CurrentRound() >= *kMaxRounds`.
  Use `std::nullopt` for genuinely unbounded games.

### Required observers

| Method | Returns |
| --- | --- |
| `GetBoard()` | `const board_t&` |
| `CurrentRound()` | `uint32_t` |
| `CurrentPlayer()` | `player_t` |
| `LastPlayer()` | `std::optional<player_t>` (nullopt before any move) |
| `LastAction()` | `std::optional<action_t>` (nullopt before any move) |
| `CanonicalBoard()` | `board_t` from the current player's perspective |
| `ValidActionsInto(out)` | writes legal actions into `out[0..count)` and returns `count`; `out` is `std::array<action_t, kMaxLegalActions>&`; deterministic, no dupes, allocation-free |
| `IsOver()` | `bool` |
| `GetScore(player)` | `float` in `[-1, +1]` from `player`'s perspective |
| `PolicyIndex(action)` | `std::size_t` in `[0, kPolicySize)`; bijection |

### Required mutation primitives

- `ApplyActionInPlace(const action_t&) -> void` — primary transition,
  must be allocation-free (it sits on the MCTS hot path).
- `UndoLastAction() -> void` — reverse the most recent apply, also
  allocation-free.

`G ApplyAction(const G&, const action_t&)` is a **free function** in the
API library. Concrete games never implement it themselves.

### Required string I/O

- `BoardReadableString() -> std::string` — printed by the REPL.
- `ActionToString(action) -> std::string` — deterministic, distinct per
  action. Round-trips with `ActionFromString`.
- `ActionFromString(string_view) -> std::expected<action_t, error_t>`.

## Output types

- `Evaluation { float value; std::vector<float> probabilities; }` — what
  the network produced. `value ∈ [-1, +1]` from the current player's
  perspective. `probabilities[i]` is the prior for the i-th action
  written by `game.ValidActionsInto(...)`.
- `TrainingTarget { float z; std::vector<float> pi; }` — what the
  network is asked to learn. `z` is the actual game outcome from
  `GetScore(state.CurrentPlayer())`. `pi[i]` is the MCTS visit-count
  prior for the i-th action written by `game.ValidActionsInto(...)`.

Deserializers produce `Evaluation`; policy serializers consume
`TrainingTarget`. Same ordering convention on both.

For compact policy heads (width proportional to `kMaxLegalActions`),
the API also ships:

- `CompactPolicyTargetBlob { float value; std::size_t count;
  std::vector<std::size_t> legal_indices; std::vector<float> values; }`
  — what `ICompactPolicyOutputSerializer<G>` produces. `legal_indices[i]`
  is `PolicyIndex(action)` for the i-th legal action; `values[i]` is
  the matching policy probability.
- `CompactPolicyOutputBlob { float value; std::span<const std::size_t>
  legal_indices; std::span<const float> values; }` — what
  `ICompactPolicyOutputDeserializer<G, E>` reads. The deserializer
  reorders into `ValidActionsInto(...)` order via `PolicyIndex`.

Compact and dense interfaces are not interchangeable; pick one for
the entire pipeline.

## Engine-owned history

The state serializer signature is

```cpp
SerializeCurrentState(const G& game, RingBufferView<G> history)
```

`history.Size() <= G::kHistoryLookback`. Index 0 is the most recent
past state preceding `game`; `game` itself is **not** in the view. The
engine owns the `RingBuffer<G>`. Markov games (`kHistoryLookback == 0`)
always see an empty view. See [history_lookback.md](./history_lookback.md).

## Augmenter contract

When `augmenter = yes`:

- `IInferenceAugmenter<G>::Augment(game) -> std::vector<G>` — return
  every equivalent position. **Convention**: `result[0]` is the
  identity. The order matches the
  `{{cookiecutter.__augmentation_enum}}` enum in
  [augmentation.h](../include/{{cookiecutter.game_slug}}/augmentation.h).
- `IInferenceAugmenter<G>::Interpret(original, augmented, evals) ->
  Evaluation` — combine per-variant evaluations back into one for
  `original`, inverting whatever symmetry was applied so the returned
  probabilities align 1:1 with the actions returned by
  `original.ValidActionsInto(...)`.
- `ITrainingAugmenter<G>::Augment(game, target) ->
  std::vector<std::pair<G, TrainingTarget>>` — return every augmented
  `(game, target)` pair. The augmented `pi[i]` corresponds to the
  i-th action returned by the augmented game's
  `ValidActionsInto(...)`. `target.z` is preserved.

See [augmentation_strategy.md](./augmentation_strategy.md) for design
guidance.

## Defaults shipped by the API

`alpha-zero-api/defaults/` provides reusable building blocks that work
out of the box for many games. See [defaults.md](./defaults.md) for
when to use them vs. roll your own.
