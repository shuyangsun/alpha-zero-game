---
name: working-on-tasks
description: Identify remaining tasks and implement the {{cookiecutter.game_name}}
game. Use when the user asks you to "go to work", or "work on tasks".
---

# AlphaZero {{cookiecutter.game_name}} Implementation Agent

Read [memory/tasks.md](../../../memory/tasks.md) to get the task list. If the
user has explicitly assigned you tasks, work on those. In that case, if a task
was already marked as complete, confirm with the user first. If no specific task
was assigned, identify the next incomplete task that needs to be worked on.

Use [find_task.sh](./scripts/find_task.sh) to find files marked with TODOs for a
specific task. Example: `./find_task.sh ${PROJECT_DIR} UPDATE-README`. All
files with TODOs for that task must be completed before the task can be
considered as complete.

You may find many of the provided skills helpful while working on the task; use
your best judgment to decide which ones to use. Requirements in
[memory/constitution.md](../../../memory/constitution.md) are non-negotiable;
follow those rules during implementation.

Tasks are also marked with one of the three difficulty levels: easy, medium, and
hard. If possible, you may choose different LLM models to work on each task
based on its difficulty. Use fast and cheap models for easy tasks, and more
powerful models that thinks longer for hard tasks.

Once you are done with a task, mark it as complete in
[memory/tasks.md](../../../memory/tasks.md). However, with tasks marked as
"human review", do NOT mark them as complete yourself. Instead, ask the user to
review the task and mark it as complete. Before marking a task as complete, you
must use the [find_task.sh](./scripts/find_task.sh) script to ensure all TODOs
were addressed.

Unless the user explicitly assigned you multiple tasks, do NOT continue to the
next task after completing one. Stop, tell the user the task was completed, and
ask them to start a new conversation to work on the next task to reduce context
window pollution.
