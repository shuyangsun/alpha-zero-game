# AlphaZero Game Template

[![Tests](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/tests.yml/badge.svg)](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/tests.yml)

A [Cookiecutter](https://github.com/cookiecutter/cookiecutter) template for bootstrapping AlphaZero game implementation of [shuyangsun/alpha-zero-api](https://github.com/shuyangsun/alpha-zero-api), which can be plugged into an [AlphaZero](https://en.wikipedia.org/wiki/AlphaZero) engine.

## Getting Started

1. Install [dependencies](#dependencies).
2. Run `uvx cookiecutter gh:shuyangsun/alpha-zero-game`.
3. Fire up your favorite LLM coding agent.
4. Type `az-agent`, let it cook.

## Dependencies

Install [uv](https://docs.astral.sh/uv/getting-started/installation/), [CMake](https://cmake.org/), [clang-format](https://clang.llvm.org/docs/ClangFormat.html), and [cmake-format](https://github.com/cheshirekow/cmake_format).

### macOS

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
brew install cmake
brew install clang-format
pip install cmakelang
```

### Linux (Debian/Ubuntu)

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
sudo apt-get install cmake clang-format
pip install cmake-format
```

### Windows

```powershell
powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"
winget install Kitware.CMake
winget install LLVM.LLVM        # includes clang-format
pip install cmake-format
```

## What if I still live in the stone age?

If you're an LLM agent, ignore the rest of the document. It is for humans who
still live under a rock. Focus on the task at hand and the skills provided to
you in the initialized game from this template.

Not everyone likes LLMs, not everyone wants to pay for tokens. And let's be
honest, some games may be too complex for current LLMs to grasp.

If you prefer to implement the game manually, or want to take a hybrid
development approach, the documentation below is intended for you.

```bash
# Specify llm="no" to turn off prompts, skills, and comments for LLMs.
uvx cookiecutter gh:shuyangsun/alpha-zero-game \
  --no-input . \
  llm="no" \
  game_name="Tic Tac Toe" \
  game_name_kebab="tic-tac-toe" \
  game_slug="ttt" \
  defaults="no" \
  github_actions="no"
  # other parameters...
```

## Build & Run

```bash
cd alpha-zero-game-<game-name-kebab-case>

# Debug
cmake --preset debug && cmake --build --preset debug

# Release
cmake --preset release && cmake --build --preset release
```

## Tests

```bash
# Build and run tests (debug)
cmake --preset debug-test && cmake --build --preset debug-test && ctest --preset debug-test

# Build and run tests (release)
cmake --preset release-test && cmake --build --preset release-test && ctest --preset release-test
```
