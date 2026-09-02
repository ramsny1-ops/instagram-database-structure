import chalk from 'chalk';
import { Command } from 'commander';
import { Member } from '../types.js';
import { loadDb, saveDb, findMember } from '../storage.js';
import { withSpinner, box, section } from '../ui.js';
import { renderTable, TableCell } from '../table.js';
import { id } from '../ids.js';
import { nowIso } from '../util.js';

export function registerMemberCommands(program: Command): void {
  const member = program
    .command('member')
    .alias('m')
    .description('Manage team members: add, list');

  member
    .command('add <name> [role]')
    .description('Add a team member')
    .action(async (name: string, role: string | undefined) => {
      const db = loadDb();
      if (db.members.some((x) => x.name.toLowerCase() === name.toLowerCase())) {
        throw new Error(`A member named "${name}" already exists`);
      }
      const created: Member = await withSpinner(`Adding ${name} to the team…`, async () => {
        const m: Member = {
          id: id('mem_'),
          name,
          role: role ?? 'Developer',
          createdAt: nowIso(),
        };
        db.members.push(m);
        saveDb();
        return m;
      }, { ms: 200, doneText: 'Member added' });
      console.log(box([chalk.bold(created.name) + chalk.dim(`  #${created.id}`), chalk.dim(created.role)], { title: ' MEMBER ' }));
    });

  member
    .command('list')
    .description('List team members with workload')
    .action(async () => {
      const db = await withSpinner('Loading members…', () => loadDb(), { doneText: 'Members loaded', ms: 150 });
      if (db.members.length === 0) {
        console.log(chalk.dim('No team members yet. Run:'));
        console.log(chalk.cyan('  pm member add "Ada Lovelace" Engineer'));
        return;
      }
      const rows: TableCell[][] = db.members.map((m) => {
        let assigned = 0;
        let open = 0;
        let hours = 0;
        for (const p of db.projects) {
          for (const t of p.tasks) {
            if (t.assigneeId === m.id) {
              assigned++;
              if (t.status !== 'done') open++;
              hours += t.timeLogs.reduce((h, l) => h + l.hours, 0);
            }
          }
        }
        return [
          m.id,
          m.name,
          m.role,
          assigned,
          { content: String(open), color: open > 3 ? 'red' : open > 0 ? 'yellow' : 'green' },
          hours.toFixed(1),
        ];
      });
      console.log(renderTable(
        ['ID', 'NAME', 'ROLE', 'TASKS', 'OPEN', 'HOURS'],
        rows,
      ));
      console.log('');
      console.log(chalk.dim('Totals:') + ` ${chalk.bold(db.members.length)} members, ` +
        `${chalk.bold(db.projects.reduce((a, p) => a + p.tasks.length, 0))} tasks`);
    });
}