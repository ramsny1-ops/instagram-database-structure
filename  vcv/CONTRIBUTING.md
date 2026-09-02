# Contributing

Thank you for wanting to contribute. This document explains how to propose
changes, report problems, and submit improvements to the schema or
documentation.

Before you begin

- Read [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).
- Search existing issues to avoid duplicates.

Reporting bugs or proposing changes

- Open an issue and include: a short summary, reproduction steps, and the
  expected behavior.
- For schema changes, include a SQL migration or a clear upgrade path.

Pull requests

- Fork the repository and create a topic branch named clearly (e.g.,
  `fix/posts-index` or `feat/story-media-duration`).
- Keep commits focused and use descriptive commit messages.
- Include tests or reproducible steps when applicable.

Working with the SQLite dump locally

- To open the schema file in the SQLite shell:

```bash
sqlite3 instagram-database.sql
```

- To inspect a table's columns:

```sql
PRAGMA table_info(posts);
```

Testing and migrations

- This repository does not include an application runtime. If you propose
  schema changes, provide an SQL migration and basic validation queries.

Style and scope

- Keep the schema portable and well-documented. Prefer explicit constraints
  and small, reversible migrations.

Contact

- For maintainer contact, see [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).
