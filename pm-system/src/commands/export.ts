import fs from 'node:fs';
import { Command } from 'commander';
import readline from 'node:readline/promises';
import { stdin as input, stdout as output } from 'node:process';
import { loadDb, currentFilePath, importDb } from '../storage.js';
import { withSpinner, ok, box } from '../ui.js';

export function registerExportImport(program: Command): void {
  program
    .command('export [file]')
    .description('Export data to a JSON backup file')
    .action(async (file: string | undefined) => {
      const outFile = file ?? `pm-backup-${Date.now()}.json`;
      const db = await withSpinner('Exporting…', () => loadDb(), { doneText: 'Loaded', ms: 150 });
      await withSpinner(`Writing ${outFile}…`, () => {
        fs.writeFileSync(outFile, JSON.stringify(db, null, 2) + '\n', 'utf8');
      }, { ms: 300, doneText: 'Export complete' });
      console.log(box([`${db.projects.length} projects, ${db.members.length} members`, '', `${outFile}`], { title: ' EXPORT ' }));
    });

  program
    .command('import <file>')
    .description('Import/restore data from a JSON backup file (replaces current data)')
    .action(async (file: string) => {
      const rl = readline.createInterface({ input, output });
      const db = loadDb();
      if (db.projects.length > 0 || db.members.length > 0) {
        console.log(box([
          `Current data has ${db.projects.length} projects and ${db.members.length} members`,
          '',
          'This will OVERWRITE the current data file',
          `  ${currentFilePath()}`,
        ], { title: ' IMPORT WARNING ' }));
        const answer = (await rl.question('Type "IMPORT" to confirm: ')).trim();
        if (answer !== 'IMPORT') {
          console.log('Cancelled.');
          rl.close();
          return;
        }
      }
      rl.close();
      await withSpinner(`Reading ${file}…`, async () => {
        if (!fs.existsSync(file)) throw new Error(`File not found: ${file}`);
        const raw = JSON.parse(fs.readFileSync(file, 'utf8'));
        importDb(raw);
      }, { ms: 300, doneText: 'Import complete' });
      ok(`Data restored from ${file}`);
    });
}