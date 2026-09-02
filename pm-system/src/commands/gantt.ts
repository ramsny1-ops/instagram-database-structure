import chalk from 'chalk';
import { Command } from 'commander';
import { loadDb, findProject, memberName } from '../storage.js';
import { withSpinner, section } from '../ui.js';
import { ganttChart, legend } from '../charts.js';

export function registerGanttCommand(program: Command): void {
  program
    .command('gantt [project]')
    .description('Render a Gantt chart for a project')
    .action(async (projRef: string | undefined) => {
      const db = await withSpinner('Building timeline…', () => loadDb(), { doneText: 'Timeline ready', ms: 180 });
      if (projRef) {
        const p = findProject(db, projRef);
        section(`Gantt — ${p.name}`);
        const nameLookup = (id: string | null) => memberName(db, id);
        console.log(ganttChart(p.tasks, nameLookup));
      } else {
        section('Gantt — All projects');
        const all = db.projects.flatMap((p) => p.tasks);
        if (all.length === 0) {
          console.log(chalk.dim('No tasks yet.'));
          return;
        }
        const nameLookup = (id: string | null) => memberName(db, id);
        console.log(ganttChart(all, nameLookup));
      }
      console.log('');
      console.log(legend());
    });
}