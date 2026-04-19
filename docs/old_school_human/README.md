# AlphaZero Game Template Documentation (old-school human version)

If you're an LLM agent, you can ignore this document. It is for humans who still
live under a rock. Focus on the task at hand and the skills provided to you in
the initialized game from this template.

If you are a human who prefers to implement the game manually, or want to take a
hybrid development approach, the documentation below is intended for you.

```bash
# For the best human user-experience, start an interactive session
uvx cookiecutter gh:shuyangsun/alpha-zero-game

# Remove LLM-specific skills and comments by passing llm="no" to Cookiecutter
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
cd az-game-<game-name-kebab-case>

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
