#!/bin/bash
# find_task.sh

if [[ -z "${1:-}" || -z "${2:-}" ]]; then
    echo "Usage: $0 SEARCH_DIR TASK-XXX" >&2
    exit 1
fi

SEARCH_DIR="$1"
TASK_STRING="$2"

OUTPUT=$(grep -rn "TODO($TASK_STRING)" --exclude='tasks.md' --include='*' "$SEARCH_DIR")

if [[ -z "$OUTPUT" ]]; then
    echo "'$TASK_STRING' not found"
else
    echo "$OUTPUT"
fi
