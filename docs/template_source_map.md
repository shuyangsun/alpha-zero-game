# AlphaZero Game Template Source Map

Date: 2026-06-12
Status: Active
Area: Cookiecutter template, generated C++ game projects, local RAG retrieval
Sources:
`README.md`, `cookiecutter.json`,
`az-game-{{cookiecutter.game_name_kebab}}/AGENTS.md`,
`az-game-{{cookiecutter.game_name_kebab}}/memory/`,
`az-game-{{cookiecutter.game_name_kebab}}/.agents/skills/`,
`hooks/post_gen_project.py`

## Summary

The AlphaZero Game Template repository is a Cookiecutter template for generating
a C++ game implementation that satisfies `alpha-zero-api`. Future retrieval about
how generated games work should start with
`az-game-{{cookiecutter.game_name_kebab}}/memory/` for project memory and
`az-game-{{cookiecutter.game_name_kebab}}/.agents/skills/` for task workflows,
then verify behavior in the generated headers, source files, tests, and
`hooks/post_gen_project.py`.

## Repository-Level Entry Points

`README.md` explains that `uvx cookiecutter gh:shuyangsun/alpha-zero-game`
generates an AlphaZero-compatible C++ game project. `cookiecutter.json` defines
the generated project variables: `game_name`, `game_name_kebab`, `game_slug`,
`defaults`, `policy_head_layout`, `augmenter`, `github_actions`, `llm`, and
`license`.

`docs/dev_dependencies.md` lists platform-specific setup for `uv`, CMake,
`clang-format`, and `cmake-format`. `docs/old_school_human/README.md` is the
manual path for users who generate a project with `llm="no"` or work without the
agent skills.

## Generated Project Layout

`az-game-{{cookiecutter.game_name_kebab}}/README.md` is the generated project's
starting readme. It records the Cookiecutter options and the CMake build/test
commands:

- `cmake --preset debug && cmake --build --preset debug`
- `cmake --preset release && cmake --build --preset release`
- `cmake --preset debug-test && cmake --build --preset debug-test && ctest --preset debug-test`
- `cmake --preset release-test && cmake --build --preset release-test && ctest --preset release-test`

`az-game-{{cookiecutter.game_name_kebab}}/AGENTS.md` tells coding agents that
the generated project implements `{{cookiecutter.game_name}}` against
`alpha-zero-api`, that `working-on-tasks` selects the next task, and that
`reviewing-code` must review code changes before they are considered done.

## Memory Docs For Retrieval

The generated `memory/` directory is the main authored context corpus for local
RAG retrieval inside generated games:

- `memory/api_contract.md` summarizes the `alpha-zero-api` `Game` concept,
  including `board_t`, `action_t`, `player_t`, `error_t`, `kHistoryLookback`,
  `kPolicySize`, `kMaxLegalActions`, `kMaxRounds`, `ValidActionsInto`,
  `PolicyIndex`, `ApplyActionInPlace`, `UndoLastAction`, string conversion,
  serializer/deserializer, and augmenter contracts.
- `memory/defaults.md` explains reusable `alpha-zero-api/defaults/` helpers such
  as board/action/player aliases, default policy serializers, and compact policy
  output serializers/deserializers.
- `memory/history_lookback.md` explains how `kHistoryLookback` maps to the
  engine-owned `RingBuffer<G>` and `RingBufferView<G>`.
- `memory/mcts_constraints.md` records MCTS hot-path constraints: value
  semantics, no virtual dispatch, allocation-free apply/undo, deterministic
  legal-action ordering, policy-index bijection, and invalid-action assumptions.
- `memory/main_binary.md` documents `src/main.cc`, the interactive REPL, debug
  serialization output, action string input, and how the REPL becomes more useful
  as tasks are completed.
- `memory/tasks.md` is the generated task graph. It links each implementation or
  test task to the skill and source paths that should be used.
- `memory/game_rules.md`, `memory/game_design.md`, and
  `memory/unittest_checklists.md` are intentionally filled in by generated-project
  tasks and become game-specific retrieval anchors.
- `memory/augmentation_strategy.md` is present when augmentation is enabled and
  explains symmetry enums, `internal::AugmentAll`, inverse action mapping,
  inference aggregation, and training target permutation.

## Generated Source And Tests

The core game interface is
`az-game-{{cookiecutter.game_name_kebab}}/include/{{cookiecutter.game_slug}}/game.h`.
The corresponding implementations live under
`az-game-{{cookiecutter.game_name_kebab}}/src/{{cookiecutter.game_slug}}/game/`:
`constructors.cc`, `basic.cc`, `state.cc`, `action.cc`, and `string_conv.cc`.

Serialization and neural-network boundary code lives in
`include/{{cookiecutter.game_slug}}/serializer.h`,
`include/{{cookiecutter.game_slug}}/deserializer.h`,
`src/{{cookiecutter.game_slug}}/serializer/serializer.cc`, and
`src/{{cookiecutter.game_slug}}/deserializer/deserializer.cc`.

When `augmenter="yes"`, augmentation code is generated in
`include/{{cookiecutter.game_slug}}/augmentation.h`,
`include/{{cookiecutter.game_slug}}/inference.h`,
`include/{{cookiecutter.game_slug}}/train.h`, and the matching
`src/{{cookiecutter.game_slug}}/{augmentation,inference,train}/` directories.

Generated unit tests live under `tests/unit/`, with one file per implementation
area: `game_constructors.cc`, `game_basic.cc`, `game_state.cc`,
`game_action.cc`, `game_string_conv.cc`, `serializer.cc`, `deserializer.cc`, and,
when augmentation is enabled, `augmentation.cc`, `inference.cc`, and `train.cc`.

## Agent Skills And Post-Generation Hook

Generated task workflows are bundled under
`az-game-{{cookiecutter.game_name_kebab}}/.agents/skills/`. Important retrieval
targets include `working-on-tasks`, `building-with-cmake`,
`finding-alpha-zero-api`, `writing-game-rule-doc`,
`writing-game-header-design-doc`, `adding-unittests`,
`updating-unittest-checklists`, `designing-serialization`, `reviewing-code`,
`reviewing-fr-test-coverage`, and `upgrading-api-version`.

`hooks/post_gen_project.py` removes optional files when `llm`, `augmenter`, or
`github_actions` are disabled, creates agent compatibility links such as
`CLAUDE.md`, `GEMINI.md`, and `.claude/skills`, formats generated C++ and CMake
files, initializes Git, commits the initial generated project, and prints the
next build commands.
