# AlphaZero Game Template

[![Tests](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/test-template.yml/badge.svg)](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/test-template.yml)

A [Cookiecutter](https://github.com/cookiecutter/cookiecutter) template for bootstrapping AlphaZero game projects with C++23 and CMake.

## Getting Started

```bash
# Install uv
# https://docs.astral.sh/uv/getting-started/installation/
curl -LsSf https://astral.sh/uv/install.sh | sh

# Update uv if it's already installed
uv self update

# Run Cookiecutter pointing to this repo
uvx cookiecutter gh:shuyangsun/alpha-zero-game
```

| Parameter        | Description                        | Examples                    |
| ---------------- | ---------------------------------- | --------------------------- |
| `game_name`      | Human-readable name of the game    | `Tic Tac Toe`               |
| `game_slug`      | Lowercase one-word game identifier | `ttt`                       |
| `github_actions` | Add GitHub Actions CI workflow     | `y`, `n`                    |
| `license`        | Project license                    | `None`, `Apache-2.0`, `MIT` |

### Build

```bash
cd ./game-name-kebab
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
