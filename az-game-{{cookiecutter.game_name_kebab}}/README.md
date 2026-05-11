# {{cookiecutter.game_name}}

**TODO(TASK-UPDATE-README)**: add a one-sentence game description for {{cookiecutter.game_name}} AlphaZero implementation.

## Cookiecutter Options

This project was generated with the following cookiecutter options:

| Option | Value |
| --- | --- |
| `game_name` | `{{cookiecutter.game_name}}` |
| `game_name_kebab` | `{{cookiecutter.game_name_kebab}}` |
| `game_slug` | `{{cookiecutter.game_slug}}` |
| `defaults` | `{{cookiecutter.defaults}}` |
| `policy_head_layout` | `{{cookiecutter.policy_head_layout}}` |
| `augmenter` | `{{cookiecutter.augmenter}}` |
| `github_actions` | `{{cookiecutter.github_actions}}` |
| `llm` | `{{cookiecutter.llm}}` |
| `license` | `{{cookiecutter.license}}` |

## Getting Started

```bash
# Debug
cmake --preset debug && cmake --build --preset debug

# Release
cmake --preset release && cmake --build --preset release

# Run interactive terminal REPL (play yourself, prints serializer
# round-trip and augmentation debug info each turn)
./build/debug/{{cookiecutter.game_slug}}    # Debug build
./build/release/{{cookiecutter.game_slug}}  # Release build
```

## Tests

```bash
# Build and run tests (debug)
cmake --preset debug-test \
  && cmake --build --preset debug-test \
  && ctest --preset debug-test

# Build and run tests (release)
cmake --preset release-test \
  && cmake --build --preset release-test \
  && ctest --preset release-test
```
