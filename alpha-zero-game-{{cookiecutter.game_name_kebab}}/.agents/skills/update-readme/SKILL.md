---
name: update-readme
description: Update high-level project description in README.md.
---

# Update README.md

Check [memory/tasks.md](../../../memory/tasks.md) to see if TASK-001 has been
completed. If not, follow instruction below; if it has been completed, ask the
user to confirm they want to update [README.md](../../../README.md) again, and
clarify what needs to be updated.

## Instructions

The user has just initialized this AlphaZero API implementation for the game
"{{cookiecutter.game_name}}", with a slug `{{cookiecutter.game_slug}}`.

If there is no ambiguity of the game and the game is well-known, update
[README.md](../../../README.md) with a short description. Stating that this repo
is an implementation of <https://github.com/shuyangsun/alpha-zero-api>.

If there is ambiguity or the game is not well-known, chat with the user to
confirm what they want before updating [README.md](../../../README.md).
