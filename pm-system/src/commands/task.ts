import chalk from 'chalk';
import { Command } from 'commander';
import { Task, Status, Priority, STATUSES, PRIORITIES, STATUS_LABEL, PRIORITY_LABEL } from '../types.js';
import { loadDb, saveDb, findProject, findTask, findTaskGlobal, findMember, taskTotalHours, memberName } from '../storage.js';
import { withSpinner, box, ok, warn, section, progressBar, truncate } from '../ui.js';
import { renderTable, TableCell } from '../table.js';
import { id } from '../ids.js';
import { nowIso, todayIso, fmtDate } from '../util.js';
import { statusCellColor, priorityCellColor } from './helpers.js';

export function registerTaskCommands(program: Command): void {
  const task = program
    .command('task')
    .alias('t')
    .description('Manage tasks: add, list, show, edit, status, assign, comment, time, search');

  task
    .command('add <project> <title>')
    .option('-s, --status <status>', 'initial status', 'todo')
    .option('-p, --priority <priority>', 'priority', 'medium')
    .option('-a, --assignee <member>', 'assignee id or name')
    .option('-d, --due <YYYY-MM-DD>', 'due date')
    .option('--start <YYYY-MM-DD>', 'start date (for Gantt)')
    .option('-t, --tags <csv>', 'comma separated tags')
    .option('-D, --desc <text>', 'description')
    .option('-e, --estimate <hours>', 'estimate in hours', '0')
    .description('Create a new task in a project')
    .action(async (projRef: string, title: string, opts: Record<string, string>) => {
      const db = loadDb();
      const project = findProject(db, projRef);

      const status = validateStatus(opts.status);
      const priority = validatePriority(opts.priority);
      const assignee = opts.assignee ? findMember(db, opts.assignee).id : null;
      const due = parseDate(opts.due, '--due');
      const start = parseDate(opts.start, '--start');
      const tags = opts.tags ? opts.tags.split(',').map((t) => t.trim()).filter(Boolean) : [];
      const estimate = parseHours(opts.estimate, '--estimate');

      const task: Task = await withSpinner(`Creating task…`, async () => {
        const t: Task = {
          id: id('tsk_'),
          title,
          description: opts.desc ?? '',
          status,
          priority,
          tags,
          assigneeId: assignee,
          dueDate: due,
          startDate: start,
          estimate,
          createdAt: nowIso(),
          comments: [],
          timeLogs: [],
        };
        project.tasks.push(t);
        saveDb();
        return t;
      }, { ms: 200, doneText: 'Task created' });

      printTaskDetail(db, project.name, task);
    });

  task
    .command('list [project]')
    .option('-s, --status <status>', 'filter by status')
    .option('-p, --priority <priority>', 'filter by priority')
    .option('-t, --tag <tag>', 'filter by tag')
    .option('-a, --assignee <member>', 'filter by assignee')
    .option('--sort <field>', 'sort by field: created|due|priority|title|status')
    .option('--order <asc|desc>', 'sort order', 'asc')
    .description('List tasks in a project, or across all projects')
    .action(async (projRef: string | undefined, opts: Record<string, string | undefined>) => {
      const db = await withSpinner('Loading tasks…', () => loadDb(), { doneText: 'Tasks loaded', ms: 150 });
      let projects = projRef ? [findProject(db, projRef)] : db.projects;
      let tasks = projects.flatMap((p) => p.tasks.map((t) => ({ project: p, task: t })));
      if (tasks.length === 0) {
        console.log(chalk.dim('No tasks to show. Run:'));
        console.log(chalk.cyan('  pm task add <project> "Task title"'));
        return;
      }
      if (opts.status) {
        const s = validateStatus(opts.status);
        tasks = tasks.filter(({ task }) => task.status === s);
      }
      if (opts.priority) {
        const p = validatePriority(opts.priority);
        tasks = tasks.filter(({ task }) => task.priority === p);
      }
      if (opts.tag) {
        const tag = opts.tag.toLowerCase();
        tasks = tasks.filter(({ task }) => task.tags.some((x) => x.toLowerCase() === tag));
      }
      if (opts.assignee) {
        const m = findMember(db, opts.assignee);
        tasks = tasks.filter(({ task }) => task.assigneeId === m.id);
      }
      // sorting
      const sortKey = opts.sort ?? 'created';
      const order = opts.order === 'desc' ? -1 : 1;
      tasks.sort((a, b) => {
        const ta = a.task, tb = b.task;
        switch (sortKey) {
          case 'title': return ta.title.localeCompare(tb.title) * order;
          case 'due': return (ta.dueDate ?? '9999-99-99').localeCompare(tb.dueDate ?? '9999-99-99') * order;
          case 'priority': return (PRIORITIES.indexOf(tb.priority) - PRIORITIES.indexOf(ta.priority)) * order;
          case 'status': return (STATUSES.indexOf(ta.status) - STATUSES.indexOf(tb.status)) * order;
          default: return ta.createdAt.localeCompare(tb.createdAt) * order;
        }
      });

      const rows: TableCell[][] = tasks.map(({ project, task: t }) => {
        const hours = taskTotalHours(t).toFixed(1);
        return [
          t.id,
          projRef ? t.title : `${chalk.dim(project.name + ' ') + t.title}`,
          { content: `| ${STATUS_LABEL[t.status]} |`, color: statusCellColor(t.status) },
          { content: `| ${PRIORITY_LABEL[t.priority]} |`, color: priorityCellColor(t.priority) },
          t.assigneeId ? memberName(db, t.assigneeId) : '—',
          t.dueDate ?? '—',
          t.estimate ? `${t.estimate}h` : '—',
          hours !== '0.0' ? hours : '—',
          t.tags.length ? t.tags.join(', ') : '',
        ];
      });
      console.log(renderTable(
        ['ID', 'TITLE', 'STATUS', 'PRIORITY', 'ASSIGNEE', 'DUE', 'EST', 'HRS', 'TAGS'],
        rows,
      ));
    });

  task
    .command('show <ref>')
    .description('Show task details, comments and time logs')
    .action(async (ref: string) => {
      const db = await withSpinner('Loading…', () => loadDb(), { doneText: 'Loaded', ms: 150 });
      const { project, task } = findTaskGlobal(db, ref);
      printTaskDetail(db, project.name, task);
    });

  task
    .command('edit <ref>')
    .option('--title <title>', 'new title')
    .option('-D, --desc <text>', 'new description')
    .option('-d, --due <YYYY-MM-DD>', 'due date (empty string to clear)')
    .option('--start <YYYY-MM-DD>', 'start date (empty string to clear)')
    .option('-e, --estimate <hours>', 'estimate in hours')
    .option('-t, --tags <csv>', 'replace tags with comma separated values')
    .description('Edit a task')
    .action(async (ref: string, opts: Record<string, string | undefined>) => {
      const db = loadDb();
      const { task: t } = findTaskGlobal(db, ref);
      await withSpinner('Updating task…', () => {
        if (opts.title !== undefined) t.title = opts.title;
        if (opts.desc !== undefined) t.description = opts.desc;
        if (opts.due !== undefined) t.dueDate = opts.due === '' ? null : parseDate(opts.due, '--due');
        if (opts.start !== undefined) t.startDate = opts.start === '' ? null : parseDate(opts.start, '--start');
        if (opts.estimate !== undefined) t.estimate = parseHours(opts.estimate, '--estimate');
        if (opts.tags !== undefined) t.tags = opts.tags ? opts.tags.split(',').map((x) => x.trim()).filter(Boolean) : [];
        saveDb();
      }, { ms: 150, doneText: 'Task updated' });
      printTaskDetail(db, '(project)', t);
    });

  task
    .command('status <ref> [newStatus]')
    .description('Show or set task status. Statuses: todo, in-progress, review, done')
    .action(async (ref: string, newStatus: string | undefined) => {
      const db = loadDb();
      const { project, task: t } = findTaskGlobal(db, ref);
      if (!newStatus) {
        console.log(`Current status: ${chalk.bold(STATUS_LABEL[t.status])}`);
        console.log('Valid statuses:', STATUSES.join(', '));
        console.log('Usage: pm task status <ref> <status>');
        return;
      }
      const s = validateStatus(newStatus);
      await withSpinner('Updating status…', () => {
        t.status = s;
        if (s === 'done') {
          if (!t.dueDate) t.dueDate = todayIso();
        }
        saveDb();
      }, { ms: 120, doneText: `Status → ${STATUS_LABEL[s]}` });
      ok(`${project.name}: "${t.title}" is now ${STATUS_LABEL[s]}`);
    });

  task
    .command('assign <ref> <member>')
    .description('Assign a task to a member')
    .action(async (ref: string, memberRef: string) => {
      const db = loadDb();
      const { project, task: t } = findTaskGlobal(db, ref);
      const m = findMember(db, memberRef);
      await withSpinner('Assigning…', () => {
        t.assigneeId = m.id;
        saveDb();
      }, { ms: 120, doneText: `Assigned → ${m.name}` });
      ok(`"${t.title}" assigned to ${m.name}`);
      void project;
    });

  task
    .command('comment <ref> [text...]')
    .option('-a, --author <name>', 'comment author (defaults to "user")')
    .description('Add a comment to a task')
    .action(async (ref: string, texts: string[] | undefined, opts: { author?: string }) => {
      if (!texts || texts.length === 0) {
        throw new Error('Comment text is required');
      }
      const text = texts.join(' ');
      const db = loadDb();
      const { task: t } = findTaskGlobal(db, ref);
      await withSpinner('Adding comment…', () => {
        t.comments.push({
          id: id('cmt_'),
          author: opts.author ?? 'user',
          body: text,
          createdAt: nowIso(),
        });
        saveDb();
      }, { ms: 120, doneText: 'Comment added' });
      ok(`Comment added to "${t.title}"`);
    });

  task
    .command('time <ref> <hours> [note...]')
    .description('Log time against a task')
    .action(async (ref: string, hoursStr: string, noteTexts: string[] | undefined) => {
      const hours = parseFloat(hoursStr);
      if (Number.isNaN(hours) || hours <= 0) throw new Error('Hours must be a positive number');
      const note = (noteTexts ?? []).join(' ');
      const db = loadDb();
      const { task: t } = findTaskGlobal(db, ref);
      await withSpinner('Logging time…', () => {
        t.timeLogs.push({ id: id('tl_'), hours, note, date: todayIso() });
        saveDb();
      }, { ms: 120, doneText: `+${hours}h logged` });
      const total = taskTotalHours(t);
      ok(`"${t.title}": ${total.toFixed(1)}h total`);
    });

  task
    .command('search <query>')
    .description('Search across all tasks by keyword')
    .action(async (query: string) => {
      const db = await withSpinner('Searching…', () => loadDb(), { doneText: 'Search complete', ms: 150 });
      const q = query.toLowerCase();
      const matches = db.projects.flatMap((p) =>
        p.tasks
          .filter((t) =>
            t.title.toLowerCase().includes(q) ||
            t.description.toLowerCase().includes(q) ||
            t.tags.some((x) => x.toLowerCase().includes(q)) ||
            (t.assigneeId && memberName(db, t.assigneeId).toLowerCase().includes(q)) ||
            p.name.toLowerCase().includes(q),
          )
          .map((t) => ({ project: p, task: t })),
      );
      if (matches.length === 0) {
        console.log(chalk.dim(`No tasks matching "${query}"`));
        return;
      }
      const rows: TableCell[][] = matches.map(({ project, task: t }) => [
        t.id,
        { content: `${chalk.dim(project.name)} / ${t.title}`, color: 'white' as const },
        { content: `| ${STATUS_LABEL[t.status]} |`, color: statusCellColor(t.status) },
        { content: `| ${PRIORITY_LABEL[t.priority]} |`, color: priorityCellColor(t.priority) },
        t.dueDate ?? '—',
      ]);
      console.log(renderTable(
        ['ID', 'PROJECT / TITLE', 'STATUS', 'PRIORITY', 'DUE'],
        rows,
      ));
    });
}

function printTaskDetail(db: ReturnType<typeof loadDb>, projectName: string, t: Task): void {
  const hours = taskTotalHours(t);
  const assignee = t.assigneeId ? memberName(db, t.assigneeId) : '—';
  const tags = t.tags.length ? t.tags.join(', ') : '—';
  console.log(box([
    chalk.bold(t.title) + chalk.dim(`  #${t.id}`),
    '',
    chalk.dim(t.description || '—'),
    '',
    `Project   ${chalk.white(projectName)}    Status   ${statusColored(t.status)}    Priority  ${priorityColored(t.priority)}`,
    `Assignee  ${chalk.white(assignee)}    Due      ${chalk.white(fmtDate(t.dueDate))}    Start     ${chalk.white(fmtDate(t.startDate))}`,
    `Estimate  ${chalk.white(t.estimate ? t.estimate + 'h' : '—')}    Logged   ${chalk.white(hours.toFixed(1) + 'h')}    Tags      ${chalk.white(tags)}`,
    '',
    t.comments.length ? `Comments  ${chalk.white(t.comments.length)}` : chalk.dim('No comments'),
  ], { title: ' TASK ' }));

  if (t.comments.length) {
    section('Comments');
    const recent = t.comments.slice(-10);
    for (const c of recent) {
      console.log(`${chalk.cyan(c.author)} ${chalk.dim(c.createdAt.slice(0, 16).replace('T', ' '))}`);
      console.log(`  ${c.body}`);
      console.log('');
    }
  }

  if (t.timeLogs.length) {
    section('Time log');
    const rows: TableCell[][] = t.timeLogs.map((l) => [l.date, `${l.hours}h`, l.note]);
    console.log(renderTable(['DATE', 'HOURS', 'NOTE'], rows));
    console.log(chalk.bold(`Total: ${hours.toFixed(1)}h`));
  }
}

function statusColored(s: Status): string { return statusCellColor(s) + ` ${STATUS_LABEL[s]} `; }
function priorityColored(p: Priority): string { return priorityCellColor(p) + ` ${PRIORITY_LABEL[p]} `; }

function validateStatus(v: string | undefined): Status {
  const s = (v ?? 'todo') as string;
  const valid = STATUSES.find((x) => x === s);
  if (!valid) throw new Error(`Invalid status: "${s}". Valid: ${STATUSES.join(', ')}`);
  return valid;
}

function validatePriority(v: string | undefined): Priority {
  const p = (v ?? 'medium') as string;
  const valid = PRIORITIES.find((x) => x === p);
  if (!valid) throw new Error(`Invalid priority: "${p}". Valid: ${PRIORITIES.join(', ')}`);
  return valid;
}

function parseDate(v: string | undefined, flag: string): string | null {
  if (!v) return null;
  if (!/^\d{4}-\d{2}-\d{2}$/.test(v)) throw new Error(`${flag} must be YYYY-MM-DD, got "${v}"`);
  return v;
}

function parseHours(v: string | undefined, flag: string): number {
  const h = parseFloat(v ?? '0');
  if (Number.isNaN(h) || h < 0) throw new Error(`${flag} must be a non-negative number, got "${v}"`);
  return h;
}