#!/usr/bin/env bash
# Replace a TASK-XXX identifier across all files in the cookiecutter template,
# excluding memory/tasks.md which should be updated manually.
# Usage: scripts/human_only/change-task-numbers.sh [--dry-run] TASK-001 TASK-002
set -euo pipefail

dry_run=0
if [[ "${1:-}" == "--dry-run" ]]; then
  dry_run=1
  shift
fi

if [[ $# -ne 2 ]]; then
  echo "Usage: $0 [--dry-run] <old-task> <new-task>" >&2
  echo "Example: $0 --dry-run TASK-001 TASK-002" >&2
  exit 1
fi

old="$1"
new="$2"

task_pattern='^TASK-[0-9]{3}$'
if ! [[ "$old" =~ $task_pattern ]]; then
  echo "Error: '$old' does not match TASK-XXX format" >&2
  exit 1
fi
if ! [[ "$new" =~ $task_pattern ]]; then
  echo "Error: '$new' does not match TASK-XXX format" >&2
  exit 1
fi

# Project root is the cookiecutter template directory
script_dir="$(cd "$(dirname "$0")" && pwd)"
project_root="$(cd "$script_dir/../.." && pwd)"
template_dir="$project_root/alpha-zero-game-{{cookiecutter.game_name_kebab}}"

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
