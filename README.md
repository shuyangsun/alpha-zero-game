# AlphaZero Game Template

A [Cookiecutter](https://github.com/cookiecutter/cookiecutter) template for bootstrapping AlphaZero game projects with C++23 and CMake.

## Getting Started

### Prerequisites

Install [uv](https://docs.astral.sh/uv/getting-started/installation/).

### Generate a New Project

```bash
uvx cookiecutter gh:shuyangsun/alpha-zero-game
```

### Parameters

| Parameter         | Description         | Examples      |
| ----------------- | ------------------- | ------------- |
| `game_name`       | Human-readable name | `Tic Tac Toe` |
| `game_name_kebab` | `game_name`         | `tic-tac-toe` |
| `game_name_snake` | `game_name`         | `tic_tac_toe` |
| `game_name_camel` | `game_name`         | `TicTacToe`   |

### Build

```bash
cd <game_name_kebab>
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
