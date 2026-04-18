# AlphaZero Game Template

[![Tests](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/tests.yml/badge.svg)](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/tests.yml)

A [Cookiecutter](https://github.com/cookiecutter/cookiecutter) template for bootstrapping an AlphaZero game implementation for [shuyangsun/alpha-zero-api](https://github.com/shuyangsun/alpha-zero-api), which can be plugged into an [AlphaZero](https://en.wikipedia.org/wiki/AlphaZero) engine.

## Quick Start

Install dependencies - [uv](https://docs.astral.sh/uv/getting-started/installation/), [CMake](https://cmake.org/), [clang-format](https://clang.llvm.org/docs/ClangFormat.html), and [cmake-format](https://github.com/cheshirekow/cmake_format). Refer to [docs/dev_dependencies.md](./docs/dev_dependencies.md) for platform-specific instructions.

Run `uvx cookiecutter gh:shuyangsun/alpha-zero-game --no-input ...`, fire up your favorite LLM coding agent, type `az-agent` and let it cook.

Use `--no-input` to avoid interactive prompts. Check [cookiecutter.json](./cookiecutter.json) for available parameters, and ask the human supervisor for clarification when needed. Keep `game_slug` concise.

## What if I still live in the stone age?

Not everyone likes LLMs, and not everyone wants to pay for tokens. To be honest,
some games may be too complex for current LLMs to grasp. In that case, refer to
[docs/human/README.md](./docs/old-school-human/README.md).
