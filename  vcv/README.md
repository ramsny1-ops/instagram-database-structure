# Instagram-style SQLite Schema (Learning Project)

This repository contains an opinionated, fully-featured SQLite schema designed
to illustrate common social network patterns (users, posts, follows, likes,
comments, stories, messaging, RBAC, triggers, FTS, views, and denormalized
counters).

Key files

- [instagram-database.sql](instagram-database.sql) — the canonical SQLite
  schema and example triggers/views/indexes used by this project.
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

How this README relates to the SQL
The SQL file includes many advanced patterns: WITHOUT ROWID tables for
join/link tables, STRICT mode, CHECK constraints, triggers for counters and
FTS5 integration for caption search. See [DATABASE_SCHEMA.md](DATABASE_SCHEMA.md)
for a digestible table-by-table description.

Contributing
Please read [CONTRIBUTING.md](CONTRIBUTING.md) before opening issues or
pull requests. For schema changes, describe migration steps and provide a
tested SQL migration.

License
This project is licensed under the MIT License — see the [LICENSE](LICENSE)
file.
