# {{cookiecutter.game_name}}

**TODO(TASK-001)**: add a one-sentence game description for {{cookiecutter.game_name}} AlphaZero implementation.

## Getting Started

```bash
# Debug
cmake --preset debug && cmake --build --preset debug

# Release
cmake --preset release && cmake --build --preset release

# Run terminal-GUI in ASCII art
./build/debug/{{cookiecutter.game_slug}}    # Debug build
./build/release/{{cookiecutter.game_slug}}  # Release build
```

## Tests

```bash
# Build and run tests (debug)
cmake --preset debug-test && cmake --build --preset debug-test && ctest --preset debug-test

# Build and run tests (release)
cmake --preset release-test && cmake --build --preset release-test && ctest --preset release-test
```
