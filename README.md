# AlphaZero Game Template

[![Tests](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/test-template.yml/badge.svg)](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/test-template.yml)

A [Cookiecutter](https://github.com/cookiecutter/cookiecutter) template for bootstrapping AlphaZero game projects with C++23 and CMake.

## Getting Started

### Prerequisites

Install [uv](https://docs.astral.sh/uv/getting-started/installation/).

### Generate a New Project

```bash
uvx cookiecutter gh:shuyangsun/alpha-zero-game
```

### Parameters

| Parameter         | Description                        | Examples                    |
| ----------------- | ---------------------------------- | --------------------------- |
| `game_name`       | Human-readable name of the game    | `Tic Tac Toe`               |
| `game_name_kebab` | Game name in kebab-case (derived)  | `tic-tac-toe`               |
| `game_slug`       | Lowercase one-word game identifier | `ttt`                       |
| `license`         | Project license                    | `None`, `Apache-2.0`, `MIT` |

### Build

```bash
cd <game_name_kebab>
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
