#!/bin/bash
# find_task.sh

if [[ -z "${1:-}" ]]; then
    echo "Usage: $0 TASK-XXX" >&2
    exit 1
fi

OUTPUT=$(grep -rn "TODO($1)" --include='*' .)

if [[ -z "$OUTPUT" ]]; then
    echo "'$1' not found"
else
    echo "$OUTPUT"
fi
