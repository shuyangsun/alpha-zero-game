# AlphaZero Game Template

[![Tests](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/test-template.yml/badge.svg)](https://github.com/shuyangsun/alpha-zero-game/actions/workflows/test-template.yml)

A [Cookiecutter](https://github.com/cookiecutter/cookiecutter) template for bootstrapping AlphaZero game projects with C++23 and CMake.

## Prerequisites

Install [uv](https://docs.astral.sh/uv/getting-started/installation/), [clang-format](https://clang.llvm.org/docs/ClangFormat.html), and [cmake-format](https://github.com/cheshirekow/cmake_format).

### macOS

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
brew install clang-format
pip install cmake-format
```

### Linux (Debian/Ubuntu)

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
sudo apt-get install clang-format
pip install cmake-format
```

### Windows

```powershell
powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"
winget install LLVM.LLVM        # includes clang-format
pip install cmake-format
```

## Getting Started

```bash
# Run Cookiecutter pointing to this repo
uvx cookiecutter gh:shuyangsun/alpha-zero-game

# Or without interactive shell
uvx cookiecutter gh:shuyangsun/alpha-zero-game \
  --no-input . \
  game_name="Tic Tac Toe" \
  game_slug="ttt" # Other parameters...
```

| Parameter        | Description                        | Examples                    |
| ---------------- | ---------------------------------- | --------------------------- |
| `game_name`      | Human-readable name of the game    | `Tic Tac Toe`               |
| `game_slug`      | Lowercase one-word game identifier | `ttt`                       |
| `github_actions` | Add GitHub Actions CI workflow     | `y`, `n`                    |
| `license`        | Project license                    | `None`, `Apache-2.0`, `MIT` |

### Build

```bash
cd ./alpha-zero-game-<game-name-kebab-case>

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

cmake --build build

./build/<game_slug>
```
