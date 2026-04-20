# AlphaZero Game Template

[![Tests](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/tests.yml/badge.svg)](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/tests.yml)

> _"You supply the rules, the machine learns the rest."_

A [Cookiecutter](https://github.com/cookiecutter/cookiecutter) template that scaffolds a fully-wired C++ game implementation for [alpha-zero-api](https://github.com/shuyangsun/alpha-zero-api), ready to plug straight into an [AlphaZero](https://en.wikipedia.org/wiki/AlphaZero) engine and start training.

Think of it as `create-react-app`, but instead of a todo list you get a board game that teaches itself to beat you.

## Quick Start

### 1. Install the toolchain

Install [uv](https://docs.astral.sh/uv/getting-started/installation/), [CMake](https://cmake.org/), [clang-format](https://clang.llvm.org/docs/ClangFormat.html), and [cmake-format](https://github.com/cheshirekow/cmake_format). Platform-specific instructions in [docs/dev_dependencies.md](./docs/dev_dependencies.md).

### 2. Generate your project

```bash
uvx cookiecutter gh:shuyangsun/alpha-zero-game
```

> Note for LLM agents: use `--no-input` to skip interactive prompts. See [cookiecutter.json](./cookiecutter.json) for available parameters, and ask the human supervisor when in doubt. Keep `game_slug` short and sweet.

### 3. Let machines do the heavy lifting

It's 2026, rocks can think.

Fire up your favorite LLM coding agent, type "**Go to work**", and let it cook.

Go grab a coffee, you've earned it.

### 4. Upgrading the API

If your API version is outdated after a while, fire up your LLM coding agent, type "**Upgrade API**". That's it. Seriously.

## What if I live under a rock?

Not everyone has embraced our robot overlords, and that's okay. Maybe you prefer
artisanal, hand-crafted code. Maybe tokens are expensive. Maybe your game's rules
would make an LLM cry.

We don't judge. Head over to
[docs/old_school_human/README.md](./docs/old_school_human/README.md) and do
things the old-fashioned way.
