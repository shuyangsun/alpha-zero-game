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

## Continue or stop after completing a task?

Check if the `/compact` skill is available. If it is and it is the start of the
a new session, ask the user if they would like to automatically compact the
conversation after marking each task as complete, then automatically continue to
the next task. If the user agrees, use the `/compact` skill after each task, and
then continue. You should use compaction in this way:

```text
/compact summarize high-level progress, keep very brief descriptions of key
decisions and reasoning, remove all other details.
```

If the user did not want to automatically continue or if the `/compact` skill is
not available, stop after each task completion and prompt the user to start a
new conversation to work on the next task to reduce context window pollution.

One exception to above rule is if the user explicitly assigned you multiple
tasks. In that case, you can continue to work on the next task with or without
compacting the conversation.
