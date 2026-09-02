import chalk from 'chalk';
import { Command } from 'commander';
import readline from 'node:readline/promises';
import { stdin as input, stdout as output } from 'node:process';
import { Project, Status, STATUSES, STATUS_LABEL, PRIORITY_LABEL } from '../types.js';
import { loadDb, saveDb, findProject } from '../storage.js';
import { withSpinner, box, ok, section, progressBar } from '../ui.js';
import { renderTable, TableCell } from '../table.js';
import { id } from '../ids.js';
import { nowIso } from '../util.js';
import { progressPlain } from '../labels.js';
import { statusCellColor, priorityCellColor } from './helpers.js';

export function registerProjectCommands(program: Command): void {
  const project = program
    .command('project')
    .description('Manage projects: create, list, show, delete');

  project
    .command('create <name> [description]')
    .description('Create a new project')
    .action(async (name: string, desc: string | undefined) => {
      const db = loadDb();
      if (db.projects.some((p) => p.name.toLowerCase() === name.toLowerCase())) {
        throw new Error(`A project named "${name}" already exists`);
      }
      const created: Project = await withSpinner('Creating project…', async () => {
        const p: Project = {
          id: id('prj_'),
          name,
          description: desc ?? '',
          createdAt: nowIso(),
          tasks: [],
        };
        db.projects.push(p);
        saveDb();
        return p;
      }, { ms: 250, doneText: 'Project created' });
      console.log(box([chalk.bold(created.name) + chalk.dim(`  #${created.id}`), '', chalk.dim(created.description)], { title: ' PROJECT ' }));
    });

  project
    .command('list')
    .description('List all projects with progress')
    .action(async () => {
      const db = await withSpinner('Loading projects…', () => loadDb(), { doneText: 'Projects loaded', ms: 150 });
      if (db.projects.length === 0) {
        console.log(chalk.dim('No projects yet. Run:'));
        console.log(chalk.cyan('  pm project create "My project"'));
        return;
      }
      const rows: TableCell[][] = db.projects.map((p) => {
        const counts = countByStatus(p);
        const ratio = p.tasks.length ? counts.done / p.tasks.length : 0;
        const statusCol = ratio < 0.34 ? 'yellow' : ratio < 0.99 ? 'cyan' : 'green';
        return [
          p.id,
          p.name,
          p.tasks.length,
          counts.todo,
          counts['in-progress'],
          counts.review,
          counts.done,
          { content: `${progressPlain(ratio)} ${barPlain(ratio)}`, color: statusCol },
        ];
      });
      console.log(renderTable(
        ['ID', 'PROJECT', 'TASKS', 'TODO', 'DOING', 'REVIEW', 'DONE', 'PROGRESS'],
        rows,
      ));
    });

  project
    .command('show <ref>')
    .description('Show a project dashboard with charts')
    .action(async (ref: string) => {
      const db = await withSpinner('Loading dashboard…', () => loadDb(), { doneText: 'Dashboard ready', ms: 150 });
      printProjectDashboard(findProject(db, ref), true);
    });

  project
    .command('delete <ref>')
    .description('Delete a project (asks for confirmation)')
    .action(async (ref: string) => {
      const db = await withSpinner('Loading…', () => loadDb(), { doneText: 'Loaded', ms: 120 });
      const p = findProject(db, ref);
      console.log(box([chalk.bold(p.name), '', chalk.dim(p.description), '', `${p.tasks.length} tasks`], { title: ' DELETE PROJECT ' }));
      const rl = readline.createInterface({ input, output });
      const answer = (await rl.question(chalk.yellow(`Type the project name "${p.name}" to confirm deletion: `))).trim();
      rl.close();
      if (answer.toLowerCase() !== p.name.toLowerCase()) {
        throw new Error('Confirmation did not match — aborting.');
      }
      await withSpinner('Deleting project…', async () => {
        db.projects = db.projects.filter((x) => x.id !== p.id);
        saveDb();
      }, { ms: 300, doneText: 'Project deleted' });
      ok(`Deleted project "${p.name}"`);
    });
}

function countByStatus(p: Project): Record<Status, number> {
  const counts: Record<Status, number> = { todo: 0, 'in-progress': 0, review: 0, done: 0 };
  for (const t of p.tasks) counts[t.status]++;
  return counts;
}

function barPlain(ratio: number): string {
  const width = 12;
  const filled = Math.round(ratio * width);
  return '█'.repeat(filled) + '░'.repeat(width - filled);
}

export function printProjectDashboard(p: Project, showTasks: boolean): void {
  const counts = countByStatus(p);
  const ratio = p.tasks.length ? counts.done / p.tasks.length : 0;
  const hours = p.tasks.reduce((sum, t) => sum + t.timeLogs.reduce((h, l) => h + l.hours, 0), 0);

  console.log(box([
    chalk.bold(p.name) + chalk.dim(`  #${p.id}`),
    '',
    chalk.dim(p.description || '—'),
    '',
    `Created  ${chalk.white(p.createdAt.slice(0, 10))}   Tasks  ${chalk.white(p.tasks.length)}   Done  ${chalk.white(counts.done)}   Hours  ${chalk.white(hours.toFixed(1))}`,
    '',
    `Progress ${progressBar(ratio)}`,
  ], { title: ' PROJECT ' }));

  section('Status distribution');
  const statusCols: Record<Status, 'gray' | 'cyan' | 'yellow' | 'green'> = {
    todo: 'gray', 'in-progress': 'cyan', review: 'yellow', done: 'green',
  };
  for (const s of STATUSES) {
    const blocks = '█'.repeat(Math.max(1, counts[s]));
    console.log(`${String(s).padEnd(12)} ${chalk[statusCols[s]](blocks)}  ${chalk.dim(counts[s])}`);
  }

  if (showTasks && p.tasks.length > 0) {
    section('Recent tasks');
    const recent = [...p.tasks].sort((a, b) => b.createdAt.localeCompare(a.createdAt)).slice(0, 8);
    const rows: TableCell[][] = recent.map((t) => [
      t.id,
      { content: t.title, color: t.status === 'done' ? 'green' : undefined },
      { content: `| ${STATUS_LABEL[t.status]} |`, color: statusCellColor(t.status) },
      { content: `| ${PRIORITY_LABEL[t.priority]} |`, color: priorityCellColor(t.priority) },
    ]);
    console.log(renderTable(['ID', 'TITLE', 'STATUS', 'PRIORITY'], rows));
  }
}