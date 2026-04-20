#!/usr/bin/env bash
# Replace a task name across all files in the cookiecutter template,
# excluding memory/tasks.md which should be updated manually.
# Usage: scripts/human_only/replace_task_name.sh <old-task> <new-task> [--apply]
set -euo pipefail

if [[ $# -lt 2 || $# -gt 3 ]]; then
  echo "Usage: $0 <old-task> <new-task> [--apply]" >&2
  echo "Example: $0 TASK-001 add-undo-support" >&2
  echo "Dry-run is the default. Pass --apply as the last argument to apply changes." >&2
  exit 1
fi

old="$1"
new="$2"

dry_run=1
if [[ $# -eq 3 ]]; then
  if [[ "$3" == "--apply" ]]; then
    dry_run=0
  else
    echo "Error: unknown option '$3' (did you mean --apply?)" >&2
    exit 1
  fi
fi

task_pattern='^[A-Za-z0-9]+([_-][A-Za-z0-9]+)*$'
if ! [[ "$old" =~ $task_pattern ]]; then
  echo "Error: '$old' is not a valid task name (use alphanumeric segments joined by - or _)" >&2
  exit 1
fi
if ! [[ "$new" =~ $task_pattern ]]; then
  echo "Error: '$new' is not a valid task name (use alphanumeric segments joined by - or _)" >&2
  exit 1
fi

# Project root is the cookiecutter template directory
script_dir="$(cd "$(dirname "$0")" && pwd)"
project_root="$(cd "$script_dir/../.." && pwd)"
template_dir="$project_root/az-game-{{cookiecutter.game_name_kebab}}"

exclude_file="memory/tasks.md"

found=0
while IFS= read -r -d '' file; do
  rel="${file#"$template_dir"/}"
  if [[ "$rel" == "$exclude_file" ]]; then
    continue
  fi
  if grep -qF "$old" "$file"; then
    if [[ "$dry_run" -eq 1 ]]; then
      echo "Would update: $rel"
      grep -nF "$old" "$file" | while IFS= read -r line; do
        echo "  $line"
      done
    else
      if [[ "$(uname)" == "Darwin" ]]; then
        sed -i '' "s|${old}|${new}|g" "$file"
      else
        sed -i "s|${old}|${new}|g" "$file"
      fi
      echo "Updated: $rel"
    fi
    found=1
  fi
done < <(find "$template_dir" -type f -print0)

if [[ "$found" -eq 0 ]]; then
  echo "No files contained '$old'"
fi
