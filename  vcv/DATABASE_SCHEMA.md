# Database Schema Overview

This document summarizes the main tables, relationships, and key columns
found in `instagram-database.sql`. Use this as a quick reference when
reviewing or proposing changes.

Top-level concepts

- Users & authentication: `users`, `user_profiles`, `auth_credentials`,
  `user_settings`, `user_stats`.
- Social graph: `follows`, `follow_requests`, `blocks`.
- Content: `posts`, `post_media`, `post_likes`, `comments`, `comment_likes`,
  `hashtags`, `post_hashtags`, `collections`, `collection_posts`.
- Stories: `stories`, `story_media`, `story_views`.
- Messaging: `conversations`, `conversation_members`, `messages`,
  `message_reactions`.
- Moderation & audit: `reports`, `moderation_actions`, `login_audit`.
- RBAC: `roles`, `permissions`, `role_permissions`, `user_roles`.

Important tables (selected columns)

- `users` — id, username, email, account_status, verified, created_at,
  updated_at, deleted_at
- `user_profiles` — user_id, display_name, bio, website, avatar_url,
  profile_visibility
- `auth_credentials` — user_id, password_hash, salt_hex, algorithm,
  iterations, failed_attempts
- `posts` — id, user_id, caption, visibility, comments_enabled,
  is_archived, created_at, deleted_at
- `post_media` — id, post_id, media_type, media_url, thumbnail_url,
  width, height, duration_ms, position
- `post_likes` — post_id, user_id, created_at
- `comments` — id, post_id, user_id, parent_comment_id, body, created_at
- `hashtags` — id, tag, usage_count
- `stories` — id, user_id, audience, created_at, expires_at
- `messages` — id, conversation_id, sender_id, message_type, body, sent_at

Views and search

- `post_search` — FTS5 virtual table for caption search (content='posts').
- `v_user_public_profile` — denormalized public profile view.
- `v_post_engagement` — post engagement counts (likes, comments, hashtags).
- `v_role_permissions`, `v_conversation_summary` — helper views.

Triggers and counters

- Many triggers maintain denormalized counters in `user_stats` (posts,
  followers/following, likes_received) and keep FTS indexes in sync.
- Soft-deletes are handled by NULLable `deleted_at` columns with triggers
  to update counters when appropriate.

Indexes

- The SQL includes focused indexes for common access patterns, e.g.
  `idx_posts_user_created`, `idx_posts_public_created`, `idx_post_likes_user_created`,
  `idx_comments_post_created`, `idx_notifications_user_unread`.

How to explore programmatically

1. Open the file in `sqlite3` and inspect tables:

```bash
sqlite3 instagram-database.sql
sqlite> .tables
sqlite> PRAGMA table_info(posts);
sqlite> SELECT * FROM v_post_engagement LIMIT 5;
```

2. To generate a portable schema SQL file, run:

```bash
sqlite3 instagram-database.sql ".schema" > schema.sql
```

Notes for contributors

- When proposing schema changes, include reversible SQL migrations and
  update this document to reflect the changes.
- Keep constraint checks and triggers explicit—this schema aims to be
  educational and production-aware.
