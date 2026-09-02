# Instagram-style SQLite Schema (Learning Project)

This repository contains an opinionated, fully-featured SQLite schema designed
to illustrate common social network patterns (users, posts, follows, likes,
comments, stories, messaging, RBAC, triggers, FTS, views, and denormalized
counters).

Key files

- [instagram-database.sql](instagram-database.sql) — the canonical SQLite schema
  and example triggers/views/indexes used by this project.
- [DATABASE_SCHEMA.md](DATABASE_SCHEMA.md) — human-readable overview of tables,
  views, and important columns (generated from the SQL dump).
- [CONTRIBUTING.md](CONTRIBUTING.md) — how to contribute.
- [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) — community expectations.
- [LICENSE](LICENSE) — MIT License.

Quick start

1. Inspect the schema with the SQLite CLI:

```bash
sqlite3 instagram-database.sql \
  ".schema" | less
```

2. Open the database and run example queries:

```bash
sqlite3 instagram-database.sql
sqlite> SELECT name FROM sqlite_master WHERE type='table';
sqlite> SELECT * FROM v_user_public_profile LIMIT 5;
```

Docker (quick browse with `sqlite-web`)

The repository includes a small `Dockerfile` that installs `sqlite-web` so you
can quickly browse the database in a web UI on port `8080`.

Build and run with Docker:

```bash
docker build -t instagram-db .
docker run --rm -p 8080:8080 instagram-db
# then open http://localhost:8080 in your browser
```

Or with Docker Compose (recommended for local development):

```bash
docker-compose up --build
# open http://localhost:8080
```

Tooling and formatting (Bun vs npm)

This repo includes a minimal `package.json` to support formatting and quick
developer scripts. You do not need Bun to use the repository, but Bun is
supported if you prefer it.

To initialize with Bun (optional):

```bash
# create or refresh package.json using bun's interactive init
bun init
bun install
bun run format
```

With npm:

```bash
npm install
npx prettier --write "**/*.{md,json,sql,js,ts}"
```

---

[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![CI](https://github.com/ramsny1-ops/instagram-sql-schema/actions/workflows/ci.yml/badge.svg)](https://github.com/ramsny1-ops/instagram-sql-schema/actions/workflows/ci.yml)
[![Release](https://github.com/ramsny1-ops/instagram-sql-schema/actions/workflows/publish.yml/badge.svg)](https://github.com/ramsny1-ops/instagram-sql-schema/actions/workflows/publish.yml)

Notes

- This repository is maintained under the GitHub account `ramsny1-ops`.
- `package.json` now contains `ramsny1-ops` values for `repository`, `bugs`, and
  `author`. Update them if you change owners or contact details.
- Prettier config files are included: `.prettierrc` and `.prettierignore`.

How this README relates to the SQL The SQL file includes many advanced patterns:
WITHOUT ROWID tables for join/link tables, STRICT mode, CHECK constraints,
triggers for counters and FTS5 integration for caption search. See
[DATABASE_SCHEMA.md](DATABASE_SCHEMA.md) for a digestible table-by-table
description.

Contributing Please read [CONTRIBUTING.md](CONTRIBUTING.md) before opening
issues or pull requests. For schema changes, describe migration steps and
provide a tested SQL migration.

License This project is licensed under the MIT License — see the
[LICENSE](LICENSE) file.
