import chalk from 'chalk';
import { Command } from 'commander';
import { STATUSES, PRIORITIES } from '../types.js';
import { loadDb, findProject, memberName } from '../storage.js';
import { withSpinner, section } from '../ui.js';
import { hbarChart, legend } from '../charts.js';
import { printProjectDashboard } from './project.js';

export function registerStatsCommand(program: Command): void {
  program
    .command('stats [project]')
    .description('Show statistics with charts for a project or the whole system')
    .action(async (projRef: string | undefined) => {
      const db = await withSpinner('Crunching numbers…', () => loadDb(), { doneText: 'Stats ready', ms: 200 });
      if (projRef) {
        const p = findProject(db, projRef);
        printProjectDashboard(p, false);
      }
      const all = db.projects.flatMap((p) => p.tasks);
      if (all.length === 0) {
        console.log(chalk.dim('No tasks to analyze. Add some tasks first.'));
        return;
      }

      section('Status breakdown');
      const statusItems = STATUSES.map((s) => ({
        label: s,
        value: all.filter((t) => t.status === s).length,
        color: s === 'todo' ? 'gray' as const : s === 'in-progress' ? 'cyan' as const : s === 'review' ? 'yellow' as const : 'green' as const,
      }));
      console.log(hbarChart('Tasks by Status', statusItems, { suffix: (v) => `${v} tasks` }));

      console.log('');
      section('Priority breakdown');
      const prioItems = PRIORITIES.map((p) => ({
        label: p,
        value: all.filter((t) => t.priority === p).length,
        color: p === 'low' ? 'blue' as const : p === 'medium' ? 'yellow' as const : p === 'high' ? 'red' as const : 'magenta' as const,
      }));
      console.log(hbarChart('Tasks by Priority', prioItems, { suffix: (v) => `${v} tasks` }));

      section('Member workload');
      const memberHours = new Map<string, number>();
      const memberTasks = new Map<string, number>();
      for (const t of all) {
        if (t.assigneeId) {
          memberHours.set(t.assigneeId, (memberHours.get(t.assigneeId) ?? 0) + t.timeLogs.reduce((a, l) => a + l.hours, 0));
          memberTasks.set(t.assigneeId, (memberTasks.get(t.assigneeId) ?? 0) + 1);
        }
      }
      if (memberHours.size === 0) {
        console.log(chalk.dim('No tasks assigned to anyone yet.'));
      } else {
        const items = [...memberHours.entries()].map(([id, hours]) => ({
          label: memberName(db, id),
          value: hours,
          color: 'cyan' as const,
        }));
        console.log(hbarChart('Hours by Member', items, { suffix: (v) => `${v}h` }));
      }

      console.log('');
      console.log(legend());
    });
}