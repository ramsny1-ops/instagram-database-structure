import chalk from 'chalk';
import { Command } from 'commander';
import { Project, Status, STATUSES } from '../types.js';
import { loadDb, findProject, memberName, taskTotalHours } from '../storage.js';
import { withSpinner, section, progressBar, box } from '../ui.js';
import { renderTable, TableCell } from '../table.js';
import { todayIso } from '../util.js';

export function registerReportCommand(program: Command): void {
  program
    .command('report [project]')
    .description('Generate a weekly status report')
    .action(async (projRef: string | undefined) => {
      const db = await withSpinner('Generating report…', () => loadDb(), { doneText: 'Report ready', ms: 200 });
      const projects = projRef ? [findProject(db, projRef)] : db.projects;
      if (projects.length === 0) {
        console.log(chalk.dim('No projects found.'));
        return;
      }

      for (const p of projects) {
        const counts: Record<Status, number> = { todo: 0, 'in-progress': 0, review: 0, done: 0 };
        const overdue: { task: import('../types.js').Task; days: number }[] = [];
        const recentDone: { task: import('../types.js').Task; hours: number }[] = [];
        const today = todayIso();

        let totalHours = 0;
        for (const t of p.tasks) {
          counts[t.status]++;
          const h = taskTotalHours(t);
          totalHours += h;
          if (t.dueDate && t.dueDate < today && t.status !== 'done') {
            const ms = new Date(today + 'T00:00:00').getTime() - new Date(t.dueDate + 'T00:00:00').getTime();
            overdue.push({ task: t, days: Math.round(ms / 86400000) });
          }
          if (t.status === 'done') recentDone.push({ task: t, hours: h });
        }

        const done = counts['done'];
        const total = p.tasks.length;
        const ratio = total ? done / total : 0;

        console.log(box([
          chalk.bold(p.name),
          '',
          `${chalk.bold('Total')} ${total} tasks    ${chalk.bold('Done')} ${done}    ${chalk.bold('Hours')} ${totalHours.toFixed(1)}h`,
          `Progress ${progressBar(ratio)}`,
          overdue.length ? `${chalk.red(`⚠ ${overdue.length} overdue tasks`)}` : chalk.green('✔ No overdue tasks'),
        ], { title: ' WEEKLY REPORT ' }));

        if (overdue.length) {
          section('Overdue');
          const rows: TableCell[][] = overdue
            .sort((a, b) => b.days - a.days)
            .map(({ task: t, days }) => [
              t.id,
              t.title,
              chalk.red(`-${days}d`),
            ]);
          console.log(renderTable(['ID', 'TASK', 'OVERDUE'], rows));
        }

        section('Status breakdown');
        for (const s of STATUSES) {
          const n = counts[s];
          const pct = total ? Math.round((n / total) * 100) : 0;
          console.log(`  ${String(s).padEnd(12)} ${String(n).padStart(4)}  (${pct}%)`);
        }

        if (recentDone.length) {
          section('Recently completed');
          const rows: TableCell[][] = recentDone.slice(-5).reverse().map(({ task: t, hours: h }) => [
            t.id,
            t.title,
            hoursCell(h),
          ]);
          console.log(renderTable(['ID', 'TASK', 'HOURS'], rows));
        }
        console.log('');
      }
    });
}

function hoursCell(h: number): string {
  return `${h.toFixed(1)}h`;
}