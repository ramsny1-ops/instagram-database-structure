PRAGMA foreign_keys = ON;
PRAGMA journal_mode = WAL;
PRAGMA synchronous = NORMAL;
PRAGMA temp_store = MEMORY;

-- Instagram-style SQLite learning schema.
-- The design intentionally exposes real relational concepts: normalization,
-- many-to-many tables, composite keys, covering indexes, triggers, views,
-- FTS5, soft deletion, RBAC, audit trails, and denormalized counters.

CREATE TABLE roles (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL UNIQUE,
  description TEXT NOT NULL,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
) STRICT;

CREATE TABLE permissions (
  id INTEGER PRIMARY KEY,
  code TEXT NOT NULL UNIQUE,
  description TEXT NOT NULL
) STRICT;

CREATE TABLE role_permissions (
  role_id INTEGER NOT NULL REFERENCES roles(id) ON DELETE CASCADE,
  permission_id INTEGER NOT NULL REFERENCES permissions(id) ON DELETE CASCADE,
  PRIMARY KEY (role_id, permission_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE users (
  id INTEGER PRIMARY KEY,
  username TEXT NOT NULL UNIQUE COLLATE NOCASE,
  email TEXT NOT NULL UNIQUE COLLATE NOCASE,
  account_status TEXT NOT NULL DEFAULT 'active' CHECK (account_status IN ('active','private','suspended','deleted')),
  verified INTEGER NOT NULL DEFAULT 0 CHECK (verified IN (0,1)),
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  deleted_at TEXT
) STRICT;

CREATE TABLE user_profiles (
  user_id INTEGER PRIMARY KEY REFERENCES users(id) ON DELETE CASCADE,
  display_name TEXT NOT NULL,
  bio TEXT NOT NULL DEFAULT '',
  website TEXT,
  location TEXT,
  avatar_url TEXT,
  birth_date TEXT,
  pronouns TEXT,
  profile_visibility TEXT NOT NULL DEFAULT 'public' CHECK (profile_visibility IN ('public','followers','private')),
  updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
) STRICT;

CREATE TABLE auth_credentials (
  user_id INTEGER PRIMARY KEY REFERENCES users(id) ON DELETE CASCADE,
  password_hash TEXT NOT NULL,
  salt_hex TEXT NOT NULL,
  algorithm TEXT NOT NULL DEFAULT 'pbkdf2_sha256',
  iterations INTEGER NOT NULL CHECK (iterations >= 100000),
  changed_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  failed_attempts INTEGER NOT NULL DEFAULT 0 CHECK (failed_attempts >= 0),
  locked_until TEXT
) STRICT;

CREATE TABLE user_roles (
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  role_id INTEGER NOT NULL REFERENCES roles(id) ON DELETE CASCADE,
  granted_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (user_id, role_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE user_settings (
  user_id INTEGER PRIMARY KEY REFERENCES users(id) ON DELETE CASCADE,
  theme TEXT NOT NULL DEFAULT 'system' CHECK (theme IN ('light','dark','system')),
  language TEXT NOT NULL DEFAULT 'en',
  push_enabled INTEGER NOT NULL DEFAULT 1 CHECK (push_enabled IN (0,1)),
  email_enabled INTEGER NOT NULL DEFAULT 1 CHECK (email_enabled IN (0,1)),
  autoplay_video INTEGER NOT NULL DEFAULT 1 CHECK (autoplay_video IN (0,1)),
  sensitive_content_filter TEXT NOT NULL DEFAULT 'standard' CHECK (sensitive_content_filter IN ('more','standard','less'))
) STRICT;

CREATE TABLE user_stats (
  user_id INTEGER PRIMARY KEY REFERENCES users(id) ON DELETE CASCADE,
  posts_count INTEGER NOT NULL DEFAULT 0 CHECK (posts_count >= 0),
  followers_count INTEGER NOT NULL DEFAULT 0 CHECK (followers_count >= 0),
  following_count INTEGER NOT NULL DEFAULT 0 CHECK (following_count >= 0),
  likes_received INTEGER NOT NULL DEFAULT 0 CHECK (likes_received >= 0)
) STRICT;

CREATE TABLE follows (
  follower_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  followee_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (follower_id, followee_id),
  CHECK (follower_id <> followee_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE follow_requests (
  requester_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  target_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  status TEXT NOT NULL DEFAULT 'pending' CHECK (status IN ('pending','accepted','rejected','cancelled')),
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  responded_at TEXT,
  PRIMARY KEY (requester_id, target_id),
  CHECK (requester_id <> target_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE blocks (
  blocker_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  blocked_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (blocker_id, blocked_id),
  CHECK (blocker_id <> blocked_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE posts (
  id INTEGER PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  caption TEXT NOT NULL DEFAULT '',
  location_name TEXT,
  visibility TEXT NOT NULL DEFAULT 'public' CHECK (visibility IN ('public','followers','close_friends','private')),
  comments_enabled INTEGER NOT NULL DEFAULT 1 CHECK (comments_enabled IN (0,1)),
  is_archived INTEGER NOT NULL DEFAULT 0 CHECK (is_archived IN (0,1)),
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  deleted_at TEXT
) STRICT;

CREATE TABLE post_media (
  id INTEGER PRIMARY KEY,
  post_id INTEGER NOT NULL REFERENCES posts(id) ON DELETE CASCADE,
  media_type TEXT NOT NULL CHECK (media_type IN ('image','video')),
  media_url TEXT NOT NULL,
  thumbnail_url TEXT,
  alt_text TEXT,
  width INTEGER CHECK (width > 0),
  height INTEGER CHECK (height > 0),
  duration_ms INTEGER CHECK (duration_ms IS NULL OR duration_ms >= 0),
  position INTEGER NOT NULL DEFAULT 0 CHECK (position >= 0),
  UNIQUE (post_id, position)
) STRICT;

CREATE TABLE post_likes (
  post_id INTEGER NOT NULL REFERENCES posts(id) ON DELETE CASCADE,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (post_id, user_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE comments (
  id INTEGER PRIMARY KEY,
  post_id INTEGER NOT NULL REFERENCES posts(id) ON DELETE CASCADE,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  parent_comment_id INTEGER REFERENCES comments(id) ON DELETE CASCADE,
  body TEXT NOT NULL CHECK (length(trim(body)) > 0),
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  deleted_at TEXT
) STRICT;

CREATE TABLE comment_likes (
  comment_id INTEGER NOT NULL REFERENCES comments(id) ON DELETE CASCADE,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (comment_id, user_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE hashtags (
  id INTEGER PRIMARY KEY,
  tag TEXT NOT NULL UNIQUE COLLATE NOCASE CHECK (length(tag) BETWEEN 1 AND 64),
  usage_count INTEGER NOT NULL DEFAULT 0 CHECK (usage_count >= 0)
) STRICT;

CREATE TABLE post_hashtags (
  post_id INTEGER NOT NULL REFERENCES posts(id) ON DELETE CASCADE,
  hashtag_id INTEGER NOT NULL REFERENCES hashtags(id) ON DELETE CASCADE,
  PRIMARY KEY (post_id, hashtag_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE collections (
  id INTEGER PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  name TEXT NOT NULL,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  UNIQUE (user_id, name)
) STRICT;

CREATE TABLE collection_posts (
  collection_id INTEGER NOT NULL REFERENCES collections(id) ON DELETE CASCADE,
  post_id INTEGER NOT NULL REFERENCES posts(id) ON DELETE CASCADE,
  saved_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (collection_id, post_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE stories (
  id INTEGER PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  audience TEXT NOT NULL DEFAULT 'followers' CHECK (audience IN ('public','followers','close_friends')),
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  expires_at TEXT NOT NULL,
  archived INTEGER NOT NULL DEFAULT 0 CHECK (archived IN (0,1))
) STRICT;

CREATE TABLE story_media (
  id INTEGER PRIMARY KEY,
  story_id INTEGER NOT NULL UNIQUE REFERENCES stories(id) ON DELETE CASCADE,
  media_type TEXT NOT NULL CHECK (media_type IN ('image','video')),
  media_url TEXT NOT NULL,
  duration_ms INTEGER CHECK (duration_ms IS NULL OR duration_ms >= 0)
) STRICT;

CREATE TABLE story_views (
  story_id INTEGER NOT NULL REFERENCES stories(id) ON DELETE CASCADE,
  viewer_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  viewed_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (story_id, viewer_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE conversations (
  id INTEGER PRIMARY KEY,
  kind TEXT NOT NULL DEFAULT 'direct' CHECK (kind IN ('direct','group')),
  title TEXT,
  created_by INTEGER REFERENCES users(id) ON DELETE SET NULL,
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
) STRICT;

CREATE TABLE conversation_members (
  conversation_id INTEGER NOT NULL REFERENCES conversations(id) ON DELETE CASCADE,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  joined_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  last_read_message_id INTEGER,
  muted INTEGER NOT NULL DEFAULT 0 CHECK (muted IN (0,1)),
  PRIMARY KEY (conversation_id, user_id)
) WITHOUT ROWID, STRICT;

CREATE TABLE messages (
  id INTEGER PRIMARY KEY,
  conversation_id INTEGER NOT NULL REFERENCES conversations(id) ON DELETE CASCADE,
  sender_id INTEGER REFERENCES users(id) ON DELETE SET NULL,
  message_type TEXT NOT NULL DEFAULT 'text' CHECK (message_type IN ('text','image','video','post_share','system')),
  body TEXT,
  shared_post_id INTEGER REFERENCES posts(id) ON DELETE SET NULL,
  sent_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  edited_at TEXT,
  deleted_at TEXT
) STRICT;

CREATE TABLE message_reactions (
  message_id INTEGER NOT NULL REFERENCES messages(id) ON DELETE CASCADE,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  reaction TEXT NOT NULL CHECK (length(reaction) BETWEEN 1 AND 16),
  reacted_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (message_id, user_id, reaction)
) WITHOUT ROWID, STRICT;

CREATE TABLE notifications (
  id INTEGER PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  actor_id INTEGER REFERENCES users(id) ON DELETE SET NULL,
  kind TEXT NOT NULL CHECK (kind IN ('follow','like','comment','mention','message','system')),
  entity_type TEXT,
  entity_id INTEGER,
  is_read INTEGER NOT NULL DEFAULT 0 CHECK (is_read IN (0,1)),
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
) STRICT;

CREATE TABLE devices (
  id INTEGER PRIMARY KEY,
  user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
  device_name TEXT NOT NULL,
  platform TEXT NOT NULL CHECK (platform IN ('ios','android','web','desktop')),
  push_token TEXT,
  last_seen_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  UNIQUE (user_id, device_name)
) STRICT;

CREATE TABLE login_audit (
  id INTEGER PRIMARY KEY,
  user_id INTEGER REFERENCES users(id) ON DELETE SET NULL,
  attempted_email TEXT NOT NULL,
  success INTEGER NOT NULL CHECK (success IN (0,1)),
  ip_address TEXT NOT NULL,
  user_agent TEXT NOT NULL,
  attempted_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
) STRICT;

CREATE TABLE reports (
  id INTEGER PRIMARY KEY,
  reporter_id INTEGER REFERENCES users(id) ON DELETE SET NULL,
  target_type TEXT NOT NULL CHECK (target_type IN ('user','post','comment','message')),
  target_id INTEGER NOT NULL,
  reason TEXT NOT NULL,
  status TEXT NOT NULL DEFAULT 'open' CHECK (status IN ('open','reviewing','resolved','dismissed')),
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
  resolved_at TEXT
) STRICT;

CREATE TABLE moderation_actions (
  id INTEGER PRIMARY KEY,
  moderator_id INTEGER REFERENCES users(id) ON DELETE SET NULL,
  report_id INTEGER REFERENCES reports(id) ON DELETE SET NULL,
  action TEXT NOT NULL CHECK (action IN ('warn','hide','delete','suspend','restore','dismiss')),
  notes TEXT NOT NULL DEFAULT '',
  created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
) STRICT;

-- High-value indexes. These mirror common query access paths rather than indexing every column.
CREATE INDEX idx_users_created_at ON users(created_at DESC);
CREATE INDEX idx_users_status_created ON users(account_status, created_at DESC);
CREATE INDEX idx_follows_followee_created ON follows(followee_id, created_at DESC);
CREATE INDEX idx_posts_user_created ON posts(user_id, created_at DESC) WHERE deleted_at IS NULL;
CREATE INDEX idx_posts_public_created ON posts(created_at DESC) WHERE visibility = 'public' AND deleted_at IS NULL AND is_archived = 0;
CREATE INDEX idx_post_media_post ON post_media(post_id, position);
CREATE INDEX idx_post_likes_user_created ON post_likes(user_id, created_at DESC);
CREATE INDEX idx_comments_post_created ON comments(post_id, created_at DESC) WHERE deleted_at IS NULL;
CREATE INDEX idx_comments_parent ON comments(parent_comment_id) WHERE parent_comment_id IS NOT NULL;
CREATE INDEX idx_post_hashtags_tag ON post_hashtags(hashtag_id, post_id);
CREATE INDEX idx_stories_user_expires ON stories(user_id, expires_at DESC);
CREATE INDEX idx_story_views_viewer ON story_views(viewer_id, viewed_at DESC);
CREATE INDEX idx_messages_conversation_sent ON messages(conversation_id, sent_at DESC);
CREATE INDEX idx_notifications_user_unread ON notifications(user_id, is_read, created_at DESC);
CREATE INDEX idx_login_audit_user_time ON login_audit(user_id, attempted_at DESC);
CREATE INDEX idx_reports_status_created ON reports(status, created_at);

-- Search index for captions. External-content FTS keeps one source of truth in posts.
CREATE VIRTUAL TABLE post_search USING fts5(
  caption,
  content='posts',
  content_rowid='id',
  tokenize='unicode61 remove_diacritics 2'
);

CREATE TRIGGER posts_ai AFTER INSERT ON posts BEGIN
  INSERT INTO post_search(rowid, caption) VALUES (new.id, new.caption);
END;
CREATE TRIGGER posts_ad AFTER DELETE ON posts BEGIN
  INSERT INTO post_search(post_search, rowid, caption) VALUES('delete', old.id, old.caption);
END;
CREATE TRIGGER posts_au AFTER UPDATE OF caption ON posts BEGIN
  INSERT INTO post_search(post_search, rowid, caption) VALUES('delete', old.id, old.caption);
  INSERT INTO post_search(rowid, caption) VALUES (new.id, new.caption);
END;

-- Maintain cached counters. These are examples of controlled denormalization.
CREATE TRIGGER users_stats_ai AFTER INSERT ON users BEGIN
  INSERT INTO user_stats(user_id) VALUES (new.id);
END;
CREATE TRIGGER follows_ai AFTER INSERT ON follows BEGIN
  UPDATE user_stats SET following_count = following_count + 1 WHERE user_id = new.follower_id;
  UPDATE user_stats SET followers_count = followers_count + 1 WHERE user_id = new.followee_id;
END;
CREATE TRIGGER follows_ad AFTER DELETE ON follows BEGIN
  UPDATE user_stats SET following_count = max(following_count - 1, 0) WHERE user_id = old.follower_id;
  UPDATE user_stats SET followers_count = max(followers_count - 1, 0) WHERE user_id = old.followee_id;
END;
CREATE TRIGGER posts_stats_ai AFTER INSERT ON posts WHEN new.deleted_at IS NULL BEGIN
  UPDATE user_stats SET posts_count = posts_count + 1 WHERE user_id = new.user_id;
END;
CREATE TRIGGER posts_stats_soft_delete AFTER UPDATE OF deleted_at ON posts
WHEN old.deleted_at IS NULL AND new.deleted_at IS NOT NULL BEGIN
  UPDATE user_stats SET posts_count = max(posts_count - 1, 0) WHERE user_id = new.user_id;
END;
CREATE TRIGGER post_likes_ai AFTER INSERT ON post_likes BEGIN
  UPDATE user_stats
  SET likes_received = likes_received + 1
  WHERE user_id = (SELECT user_id FROM posts WHERE id = new.post_id);
END;
CREATE TRIGGER post_likes_ad AFTER DELETE ON post_likes BEGIN
  UPDATE user_stats
  SET likes_received = max(likes_received - 1, 0)
  WHERE user_id = (SELECT user_id FROM posts WHERE id = old.post_id);
END;
CREATE TRIGGER post_hashtags_ai AFTER INSERT ON post_hashtags BEGIN
  UPDATE hashtags SET usage_count = usage_count + 1 WHERE id = new.hashtag_id;
END;
CREATE TRIGGER post_hashtags_ad AFTER DELETE ON post_hashtags BEGIN
  UPDATE hashtags SET usage_count = max(usage_count - 1, 0) WHERE id = old.hashtag_id;
END;

CREATE TRIGGER users_updated_at AFTER UPDATE ON users
WHEN new.updated_at = old.updated_at BEGIN
  UPDATE users SET updated_at = CURRENT_TIMESTAMP WHERE id = new.id;
END;

CREATE VIEW v_user_public_profile AS
SELECT
  u.id,
  u.username,
  p.display_name,
  p.bio,
  p.website,
  p.location,
  u.verified,
  u.account_status,
  s.posts_count,
  s.followers_count,
  s.following_count,
  s.likes_received,
  u.created_at
FROM users u
JOIN user_profiles p ON p.user_id = u.id
JOIN user_stats s ON s.user_id = u.id
WHERE u.deleted_at IS NULL;

CREATE VIEW v_post_engagement AS
SELECT
  p.id AS post_id,
  p.user_id,
  u.username,
  p.caption,
  p.created_at,
  COUNT(DISTINCT l.user_id) AS likes,
  COUNT(DISTINCT c.id) AS comments,
  COUNT(DISTINCT ph.hashtag_id) AS hashtags
FROM posts p
JOIN users u ON u.id = p.user_id
LEFT JOIN post_likes l ON l.post_id = p.id
LEFT JOIN comments c ON c.post_id = p.id AND c.deleted_at IS NULL
LEFT JOIN post_hashtags ph ON ph.post_id = p.id
WHERE p.deleted_at IS NULL
GROUP BY p.id;

CREATE VIEW v_role_permissions AS
SELECT r.name AS role, p.code AS permission
FROM roles r
JOIN role_permissions rp ON rp.role_id = r.id
JOIN permissions p ON p.id = rp.permission_id;

CREATE VIEW v_conversation_summary AS
SELECT
  c.id AS conversation_id,
  c.kind,
  c.title,
  COUNT(DISTINCT cm.user_id) AS member_count,
  COUNT(m.id) AS message_count,
  MAX(m.sent_at) AS last_message_at
FROM conversations c
LEFT JOIN conversation_members cm ON cm.conversation_id = c.id
LEFT JOIN messages m ON m.conversation_id = c.id AND m.deleted_at IS NULL
GROUP BY c.id;
