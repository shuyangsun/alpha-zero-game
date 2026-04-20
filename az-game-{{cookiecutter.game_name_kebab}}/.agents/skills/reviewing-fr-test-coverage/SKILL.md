---
name: reviewing-fr-test-coverage
description: Review functional requirements test coverage based on unittest checklists.
---

# Reviewing Functional Requirements Test Coverage

Tests were added to [tests/unit/](../../../tests/unit/) based on the unittest
checklists in [memory/unittest_checklists.md](../../../memory/unittest_checklists.md).
Use [find_fr.sh](../../../.agents/skills/adding-unittests/scripts/find_fr.sh)
`tests/unit/ FR-...` to find test files with specific `FR` identifiers. Mark
the checklist items as complete in `unittest_checklists.md` if there are tests
implemented for those functional requirements.
