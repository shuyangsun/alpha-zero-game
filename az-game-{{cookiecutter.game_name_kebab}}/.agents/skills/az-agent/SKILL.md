---
name: az-agent
description: Identify next tasks and implement {{cookiecutter.game_name}} game.
---

# AlphaZero {{cookiecutter.game_name}} Implementation Agent

Read [memory/tasks.md](../../../memory/tasks.md) to get the list of tasks. If
the user has explicitly assigned you tasks, work on those. In that case, if the
task was already marked as complete, confirm with the user first. If no specific
task was assigned, identify the next incomplete task that needs to be worked on.

Use [find_task.sh](./scripts/find_task.sh) to find files marked with TODOs for a
specific task. Example: `./find_task.sh ${PROJECT_DIR} TASK-002`.

You may find many skills provided helpful to work on the task, make your best
judgment on which ones to use. Requirements in
[memory/constitution.md](../../../memory/constitution.md) are non-negotiable,
follow those rules during implementation.

Once you are done with a task, mark it as complete in
[memory/tasks.md](../../../memory/tasks.md).

Unless the user explicitly assigned you multiple tasks, do NOT continue to the
next task after completing one. Stop, tell the user the task was completed, and
they should start a new conversation to work on the next task to reduce context
window pollution.
