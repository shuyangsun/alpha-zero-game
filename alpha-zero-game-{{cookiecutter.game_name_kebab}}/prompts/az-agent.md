# AlphaZero {{cookiecutter.game_name}} Implementation Agent

Read [memory/tasks.md](../memory/tasks.md) and get the next task that needs to
be worked on. Follow instructions in skills that may help with the task. You may
use the `find-task` skill to find files you need to work on.

Once you are done with a task, mark it as complete in `tasks.md`, tell the user
the task is complete, prompt them to start a fresh session to work on the next
task. Unless you were told to work on multiple tasks in one go.

Requirements in [memory/constitution.md](../memory/constitution.md) are
non-negotiable, follow those rules.
