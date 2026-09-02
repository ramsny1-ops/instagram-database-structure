import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { DB, Project, Task, Member } from './types.js';
import { nowIso } from './util.js';
import { id } from './ids.js';

function defaultPath(): string {
  const env = process.env.PM_DATA_FILE;
  if (env) return env;
  return path.join(os.homedir(), '.pm', 'data.json');
}

let cache: DB | null = null;
let filePath: string | null = null;

export function currentFilePath(): string {
  if (!filePath) filePath = defaultPath();
  return filePath;
}

export function emptyDb(): DB {
  const now = nowIso();
  return { version: 1, createdAt: now, updatedAt: now, projects: [], members: [] };
}

export function loadDb(reload = false): DB {
  if (cache && !reload) return cache;
  const file = currentFilePath();
  try {
    if (fs.existsSync(file)) {
      const raw = JSON.parse(fs.readFileSync(file, 'utf8')) as DB;
      if (raw && raw.version && Array.isArray(raw.projects) && Array.isArray(raw.members)) {
        cache = raw;
        return raw;
      }
    }
  } catch (err) {
    cache = null;
    throw new Error(`Corrupted data file ${file}: ${(err as Error).message}`);
  }
  cache = emptyDb();
  return cache;
}

export function saveDb(): DB {
  const db = loadDb();
  db.updatedAt = nowIso();
  const file = currentFilePath();
  fs.mkdirSync(path.dirname(file), { recursive: true });
  fs.writeFileSync(file, JSON.stringify(db, null, 2) + '\n', 'utf8');
  return db;
}

export function resetCache(): void {
  cache = null;
}

export function importDb(raw: unknown): DB {
  const db = raw as DB;
  if (!db || typeof db !== 'object') throw new Error('Invalid database file: not an object');
  if (!Array.isArray(db.projects) || !Array.isArray(db.members)) {
    throw new Error('Invalid database file: missing projects/members arrays');
  }
  db.version = 1;
  db.updatedAt = nowIso();
  cache = db;
  saveDb();
  return db;
}

// ---- lookups ----

export function findProject(db: DB, ref: string): Project {
  const p = db.projects.find((x) => x.id === ref || x.name.toLowerCase() === ref.toLowerCase());
  if (!p) throw new Error(`Project not found: ${ref}`);
  return p;
}

export function findTask(project: Project, ref: string): Task {
  const t = project.tasks.find(
    (x) => x.id === ref || x.title.toLowerCase() === ref.toLowerCase(),
  );
  if (!t) throw new Error(`Task not found in project "${project.name}": ${ref}`);
  return t;
}

export function findTaskGlobal(db: DB, ref: string): { project: Project; task: Task } {
  for (const project of db.projects) {
    const task = project.tasks.find((x) => x.id === ref);
    if (task) return { project, task };
  }
  throw new Error(`Task not found: ${ref}`);
}

export function findMember(db: DB, ref: string): Member {
  const m = db.members.find((x) => x.id === ref || x.name.toLowerCase() === ref.toLowerCase());
  if (!m) throw new Error(`Member not found: ${ref}`);
  return m;
}

export function taskTotalHours(task: Task): number {
  return task.timeLogs.reduce((sum, t) => sum + t.hours, 0);
}

export function memberName(db: DB, id: string | null): string {
  if (!id) return '—';
  const m = db.members.find((x) => x.id === id);
  return m ? m.name : 'unknown';
}