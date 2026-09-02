import chalk from 'chalk';
import { Command } from 'commander';
import { Project, Task, Member } from '../types.js';
import { loadDb, saveDb, currentFilePath, emptyDb } from '../storage.js';
import { withSpinner, banner, ok, box, info } from '../ui.js';
import { id } from '../ids.js';
import { nowIso, addDaysIso, todayIso } from '../util.js';

export function registerDemoCommand(program: Command): void {
  program
    .command('demo')
    .option('--force', 'replace existing data without asking')
    .description('Seed the database with rich sample data')
    .action(async (opts: { force?: boolean }) => {
      banner('PM Demo', 'Slant');

      const db = loadDb();
      if ((db.projects.length > 0 || db.members.length > 0) && !opts.force) {
        console.log(box([`${db.projects.length} projects, ${db.members.length} members already exist`, '', 'Run with --force to replace data'], { title: ' WARNING ' }));
        return;
      }

      const data = await withSpinner('Generating sample data…', async () => buildDemoDb(), { ms: 600, doneText: 'Demo data ready' });

      // overwrite
      Object.assign(db, data);
      saveDb();

      ok(`Seeded ${db.projects.length} projects with ${db.projects.reduce((a, p) => a + p.tasks.length, 0)} tasks`);
      info(`Data file: ${currentFilePath()}`);
      console.log('');
      console.log(chalk.dim('Try these commands next:'));
      console.log(chalk.cyan('  pm project list'));
      console.log(chalk.cyan('  pm project show phoenix'));
      console.log(chalk.cyan('  pm gantt'));
      console.log(chalk.cyan('  pm stats'));
      console.log(chalk.cyan('  pm report'));
    });
}

function buildDemoDb() {
  const today = todayIso();
  const t = (d: number) => addDaysIso(today, d);

  const members: Member[] = [
    { id: 'mem_alice', name: 'Alice', role: 'Tech Lead', createdAt: nowIso() },
    { id: 'mem_bob', name: 'Bob', role: 'Backend Dev', createdAt: nowIso() },
    { id: 'mem_carla', name: 'Carla', role: 'Frontend Dev', createdAt: nowIso() },
    { id: 'mem_dave', name: 'Dave', role: 'Designer', createdAt: nowIso() },
    { id: 'mem_eve', name: 'Eve', role: 'QA Engineer', createdAt: nowIso() },
  ];

  const m = (name: string) => members.find((x) => x.name === name)!.id;

  const phoenix = makeProject('Phoenix', 'New customer dashboard with real-time analytics', [
    task('Set up database schema', 'done', 'high', 'alice', [-14, -12], [
      { text: 'Used PostgreSQL for time series data', author: 'Alice' },
    ], [
      { hours: 6, note: 'Schema design' },
    ], ['backend', 'database'], 8),

    task('Build auth API', 'done', 'high', 'bob', [-12, -8], [
      { text: 'JWT with refresh tokens implemented', author: 'Bob' },
    ], [
      { hours: 8, note: 'Core auth' },
      { hours: 4, note: 'Unit tests' },
    ], ['backend', 'auth'], 12),

    task('Dashboard UI mockups', 'done', 'medium', 'dave', [-10, -6], [
      { text: 'Approved by product team', author: 'Dave' },
    ], [
      { hours: 12, note: 'Figma + review' },
    ], ['design', 'ui'], 16),

    task('Build dashboard components', 'in-progress', 'high', 'carla', [-7, 3], [], [
      { hours: 16, note: 'React components' },
    ], ['frontend', 'ui'], 24),

    task('Real-time WebSocket layer', 'in-progress', 'critical', 'bob', [-5, 2], [
      { text: 'Working on heartbeat mechanism', author: 'Bob' },
    ], [
      { hours: 10, note: 'Socket.io setup' },
    ], ['backend', 'real-time'], 16),

    task('Integrate analytics charts', 'todo', 'medium', 'carla', [0, 5], [], [], ['frontend', 'charts'], 10),

    task('Performance testing', 'todo', 'high', 'eve', [4, 8], [], [], ['qa', 'performance'], 12),

    task('Security audit', 'todo', 'critical', 'alice', [6, 10], [], [], ['security'], 20),

    task('Documentation', 'review', 'low', 'alice', [2, 7], [], [
      { hours: 4, note: 'API docs draft' },
    ], ['docs'], 6),

    task('Deploy to staging', 'todo', 'medium', 'bob', [8, 10], [], [], ['devops'], 4),
  ]);

  const atlas = makeProject('Atlas', 'Migrating legacy billing system to microservices', [
    task('Analyze legacy codebase', 'done', 'high', 'alice', [-20, -14], [
      { text: 'Fully mapped the invoice module', author: 'Alice' },
    ], [
      { hours: 12, note: 'Code review' },
    ], ['analysis'], 10),

    task('Design microservice boundaries', 'done', 'critical', 'alice', [-14, -10], [
      { text: 'Finalized service boundaries', author: 'Alice' },
      { text: 'AGREED: separate payment gateway service', author: 'Bob' },
    ], [
      { hours: 10, note: 'Architecture docs' },
    ], ['architecture'], 12),

    task('Build payment service', 'in-progress', 'high', 'bob', [-8, 4], [
      { text: 'Stripe integration complete', author: 'Bob' },
    ], [
      { hours: 14, note: 'Stripe integration' },
    ], ['backend', 'payments'], 16),

    task('Invoice service migration', 'todo', 'high', 'carla', [0, 10], [], [], ['backend', 'billing'], 20),

    task('Build billing UI', 'todo', 'medium', 'carla', [4, 14], [], [], ['frontend', 'ui'], 18),

    task('Data migration scripts', 'review', 'critical', 'alice', [-2, 2], [
      { text: 'Scripts ready for testing', author: 'Alice' },
    ], [
      { hours: 8, note: 'ETL pipelines' },
    ], ['data', 'migration'], 12),

    task('End-to-end tests', 'todo', 'medium', 'eve', [10, 16], [], [], ['qa'], 16),

    task('Blue-green deployment', 'todo', 'high', 'bob', [14, 18], [], [], ['devops'], 8),
  ]);

  return { version: 1, createdAt: nowIso(), updatedAt: nowIso(), projects: [phoenix, atlas], members };
}

type CommentInput = { text: string; author: string };
type TimeInput = { hours: number; note: string };

function makeProject(name: string, description: string, tasks: Task[]): Project {
  return {
    id: id('prj_'),
    name,
    description,
    createdAt: nowIso(),
    tasks,
  };
}

function task(
  title: string,
  status: import('../types.js').Status,
  priority: import('../types.js').Priority,
  assigneeName: string,
  dateRange: [number, number],
  comments: CommentInput[],
  timeLogs: TimeInput[],
  tags: string[],
  estimate: number,
): Task {
  const m: Record<string, string> = {
    alice: 'mem_alice', bob: 'mem_bob', carla: 'mem_carla', dave: 'mem_dave', eve: 'mem_eve',
  };
  return {
    id: id('tsk_'),
    title,
    description: '',
    status,
    priority,
    tags,
    assigneeId: m[assigneeName] ?? null,
    startDate: addDaysIso(todayIso(), dateRange[0]),
    dueDate: addDaysIso(todayIso(), dateRange[1]),
    estimate,
    createdAt: nowIso(),
    comments: comments.map((c) => ({
      id: id('cmt_'),
      author: c.author,
      body: c.text,
      createdAt: nowIso(),
    })),
    timeLogs: timeLogs.map((l) => ({
      id: id('tl_'),
      hours: l.hours,
      note: l.note,
      date: nowIso(),
    })),
  };
}