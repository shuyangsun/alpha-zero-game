---
name: working-on-tasks
description: Identify remaining tasks and implement the {{cookiecutter.game_name}}
game. Use when the user asks you to "go to work", or "work on tasks".
---

# AlphaZero {{cookiecutter.game_name}} Implementation Agent

## Pick a task

- If the user assigned specific task(s), work on those. If an assigned task is
  already marked `[x]`, confirm with the user before redoing it.
- Otherwise, run [next_task.sh](./scripts/next_task.sh) to get the next
  incomplete task as a short snippet. **Do NOT read the full
  [memory/tasks.md](../../../memory/tasks.md)** — it is large and pollutes the
  context window.

  ```
  ./scripts/next_task.sh ${PROJECT_DIR}/memory/tasks.md
  ```

## Work the task

- Run [find_task.sh](./scripts/find_task.sh) to locate all TODOs for the task
  (e.g. `./find_task.sh ${PROJECT_DIR} UPDATE-README`). Every TODO must be
  resolved before the task is complete.
- [memory/constitution.md](../../../memory/constitution.md) is non-negotiable.
- Match model strength to task difficulty (fast/cheap for `easy`, strong and
  longer-thinking for `hard`) when the harness allows it.
- Use whichever other skills fit the task.

## Finish the task

- Rerun [find_task.sh](./scripts/find_task.sh) to confirm no TODOs remain.
- Flip the task's `[ ]` to `[x]` on its line in
  [memory/tasks.md](../../../memory/tasks.md). `next_task.sh` prints the exact
  line number — edit just that line; don't read the whole file.
- **Exception:** if `HRR = Yes`, leave it unchecked and ask the user to review
  and mark it complete.

## Continue or stop?

Context window hygiene matters: finishing one task then stopping keeps future
sessions fast and focused. Decide what to do next using this order:

1. **Multiple assigned tasks.** Continue to the next assigned task. Compact
   between tasks if the conversation is getting long.
2. **Start of a new session and `/compact` is available.** Ask the user *once*
   whether they'd like you to auto-compact after each task and continue to the
   next. If they agree, use the command below after marking the task complete,
   then rerun `next_task.sh` and proceed.
3. **Otherwise.** Stop after one task. Report completion and suggest starting a
   new conversation for the next task.

Use `/compact` with this phrasing so only the essentials survive:

```text
/compact summarize high-level progress, keep very brief descriptions of key
decisions and reasoning, remove all other details.
```
