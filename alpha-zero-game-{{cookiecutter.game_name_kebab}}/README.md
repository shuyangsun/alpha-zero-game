# {{cookiecutter.game_name}}

**TODO(Task-001)**: add one-sentence game description based on game name.

## Build

```bash
# Debug
cmake --preset debug && cmake --build --preset debug

# Release
cmake --preset release && cmake --build --preset release
```

## Run

```bash
./build/debug/{{cookiecutter.game_slug}}    # Debug build
./build/release/{{cookiecutter.game_slug}}  # Release build
```
