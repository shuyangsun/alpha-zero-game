#!/bin/bash
# test_fetch_migration_guides.sh
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_ROOT"

CMAKE_FILE="CMakeLists.txt"
MEM_FILE="memory/migrations.md"

# Save original version so we can restore it
ORIGINAL_VER=$(./scripts/parse_current_api_ver.sh)

# Ensure CMakeLists.txt is restored on exit (step 4), even on failure
restore_version() {
    perl -0777 -pi -e "s/(ALPHA_ZERO_API_GIT_TAG\s+)\"[^\"]+\"/\$1\"$ORIGINAL_VER\"/" "$CMAKE_FILE"
}
trap restore_version EXIT

# 1. Change ALPHA_ZERO_API_GIT_TAG in CMakeLists.txt to v0.0.0.
#    Uses perl -0777 to slurp the entire file so \s+ spans newlines (multi-line case).
perl -0777 -pi -e 's/(ALPHA_ZERO_API_GIT_TAG\s+)"[^"]+"/$1"v0.0.0"/' "$CMAKE_FILE"

CURRENT_VER=$(./scripts/parse_current_api_ver.sh)
if [ "$CURRENT_VER" != "v0.0.0" ]; then
    echo "FAIL: Expected version v0.0.0 but got $CURRENT_VER" >&2
    exit 1
fi

# 2. Run fetch_migration_guides.sh.
./scripts/fetch_migration_guides.sh

# 3. Make sure memory/migrations.md has a checklist item to upgrade from v0.0.0.
if grep -q '^- \[ \] \[`v0\.0\.0` to `v' "$MEM_FILE"; then
    echo "PASS: Found migration checklist item from v0.0.0"
else
    echo "FAIL: No migration checklist item from v0.0.0 found in $MEM_FILE" >&2
    exit 1
fi

# 4. Restore handled by the EXIT trap (restore_version).
RESTORED_VER=$(./scripts/parse_current_api_ver.sh)
echo "PASS: All tests passed (version will be restored to $ORIGINAL_VER)"
