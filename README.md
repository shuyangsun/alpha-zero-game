# AlphaZero Game Template

[![Tests](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/tests.yml/badge.svg)](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/tests.yml)

A [Cookiecutter](https://github.com/cookiecutter/cookiecutter) template for bootstrapping an AlphaZero game implementation for [shuyangsun/alpha-zero-api](https://github.com/shuyangsun/alpha-zero-api), which can be plugged into an [AlphaZero](https://en.wikipedia.org/wiki/AlphaZero) engine.

## Quick Start

Install dependencies - [uv](https://docs.astral.sh/uv/getting-started/installation/), [CMake](https://cmake.org/), [clang-format](https://clang.llvm.org/docs/ClangFormat.html), and [cmake-format](https://github.com/cheshirekow/cmake_format). Refer to [docs/dev_dependencies.md](./docs/dev_dependencies.md) for platform-specific instructions.

Run `uvx cookiecutter gh:shuyangsun/alpha-zero-game`, fire up your favorite LLM coding agent, type `/az-agent start cooking!`.

> If you're an LLM agent, use `--no-input` to avoid interactive prompts. Check [cookiecutter.json](./cookiecutter.json) for available parameters, and ask the human supervisor for clarification when needed. Keep `game_slug` concise.

## What if I live under a rock?

Not everyone likes LLMs, not everyone wants to pay for tokens, some games' rules
may be too complex for today's LLMs.

In that case, refer to
[docs/old_school_human/README.md](./docs/old_school_human/README.md).
