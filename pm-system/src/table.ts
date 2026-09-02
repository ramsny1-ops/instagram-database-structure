import Table from 'cli-table3';
import { Color } from './ui.js';

export type TableCell = string | number | { content: string; color?: Color };

const CHARS = {
  top: '─',
  'top-mid': '┬',
  'top-left': '┌',
  'top-right': '┐',
  bottom: '─',
  'bottom-mid': '┴',
  'bottom-left': '└',
  'bottom-right': '┘',
  left: '│',
  'left-mid': '├',
  mid: '─',
  'mid-mid': '┼',
  right: '│',
  'right-mid': '┤',
  middle: '│',
};

export function renderTable(head: string[], rows: TableCell[][], opts: { maxWidth?: number } = {}): string {
  const table = Table({
    head,
    chars: CHARS,
    style: {
      head: ['cyan', 'bold'],
      border: ['gray'],
      'padding-left': 1,
      'padding-right': 1,
    },
  });
  for (const row of rows) {
    const cells = row.map((cell) => {
      if (typeof cell === 'object' && cell !== null && 'content' in cell) {
        const { color } = cell as { content: string; color?: Color };
        return { content: (cell as { content: string }).content, color } as Record<string, string | number>;
      }
      return cell;
    });
    table.push(cells);
  }
  const rendered = table.toString();
  if (opts.maxWidth && process.stdout.columns && rendered.length > 0) {
    return `${table.toString()}\n${dimRow('… truncated …')}`;
  }
  return rendered;
}

function dimRow(text: string): string {
  return text;
}