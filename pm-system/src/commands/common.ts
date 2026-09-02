import chalk from 'chalk';
import { Command } from 'commander';
import { fail, banner } from '../ui.js';

export function makeProgram(): Command {
  const program = new Command();
  program
    .name('pm')
    .description(chalk.cyan('PM System — a project management suite for the terminal (20+ features)'))
    .version('1.0.0');

  program.action(() => showMenu());

  return program;
}

export function run(
  fn: (...args: unknown[]) => void | Promise<void>,
): (...args: unknown[]) => Promise<void> {
  return async (...args) => {
    try {
      await fn(...args);
    } catch (err) {
      const message = err instanceof Error ? err.message : String(err);
      fail(message);
      process.exitCode = 1;
    }
  };
}

export function showMenu(): void {
  banner('PM System');
  const items = [
    ['project create <name>', 'Start a new project'],
    ['project list', 'List projects with progress'],
    ['project show <ref>', 'Project dashboard'],
    ['project delete <ref>', 'Remove a project'],
    ['member add <name> [role]', 'Add a team member'],
    ['member list', 'List team members'],
    ['task add <project> <title>', 'Create a task (use -c for more options)'],
    ['task list [project]', 'List tasks (filter & sort)'],
    ['task show <ref>', 'Task detail view'],
    ['task edit <ref>', 'Edit task fields'],
    ['task status <ref> <status>', 'Move task between statuses'],
    ['task assign <ref> <member>', 'Assign a task'],
    ['task comment <ref> <text>', 'Comment on a task'],
    ['task time <ref> <hours>', 'Log time on a task'],
    ['task search <query>', 'Search across all tasks'],
    ['gantt [project]', 'Render a Gantt chart'],
    ['stats [project]', 'Statistics with charts'],
    ['report [project]', 'Weekly report'],
    ['export [file]', 'Backup data to JSON'],
    ['import <file>', 'Restore data from JSON'],
    ['demo', 'Seed the database with sample data'],
  ];
  const pad = Math.max(...items.map(([c]) => c.length));
  console.log(chalk.dim('Features:'));
  for (const [cmd, desc] of items) {
    console.log(`  ${chalk.bold.green(cmd.padEnd(pad + 2))}${chalk.dim(desc)}`);
  }
  console.log('');
  console.log(chalk.dim('Run') + chalk.cyan(' pm <command> --help ') + chalk.dim('for details on any command.'));
}