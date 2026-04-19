---
name: az-upgrade-api
description: Migration guide for upgrading to the newer API versions.
---

## Upgrade API Version

Run [.agents/skills/az-upgrade-api/scripts/fetch_migration_guides.sh](./scripts/fetch_migration_guides.sh)
to fetch the latest migration guides, which will be added to [memory/migrations.md](../../../memory/migrations.md).

Work on incomplete items in `migrations.md` in order, following the linked
instructions.

Note that instead of upgrading to the highest API version in migration guides,
you should upgrade to the highest API version available. For example, if the
latest migration guide was from `v0.0.0` to `v0.0.2`, but
[.agents/skills/az-upgrade-api/scripts/fetch_latest_api_ver.sh](./scripts/fetch_latest_api_ver.sh)
shows that the latest API version is `v0.0.3`, you should upgrade to `v0.0.3`
after finishing all migration items.

Make sure the project still builds and all tests pass after the upgrade, use the
`build-instructions` skill if you don't know how.
