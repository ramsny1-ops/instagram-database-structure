import chalk from 'chalk';
import figlet from 'figlet';
import { mind, atlas } from 'gradient-string';
import { delay } from './util.js';

export type Color = 'red' | 'green' | 'yellow' | 'blue' | 'magenta' | 'cyan' | 'gray' | 'white';

function fg(color: Color): (s: string) => string {
  switch (color) {
    case 'red': return chalk.red;
    case 'green': return chalk.green;
    case 'yellow': return chalk.yellow;
    case 'blue': return chalk.blue;
    case 'magenta': return chalk.magenta;
    case 'cyan': return chalk.cyan;
    case 'gray': return chalk.gray;
    default: return chalk.white;
  }
}

export function banner(text: string, font: string = 'Standard'): void {
  try {
    const art = figlet.textSync(text, { font, horizontalLayout: 'full' });
    console.log('\n' + mind(art) + '\n');
  } catch {
    console.log(chalk.bold(text));
  }
}

export function rule(char = '─', len = process.stdout.columns ? Math.min(process.stdout.columns, 72) : 72): string {
  return chalk.dim(char.repeat(Math.max(10, len)));
}

export function section(title: string): void {
  const width = process.stdout.columns ? Math.min(process.stdout.columns, 72) : 72;
  const titleTxt = ` ${chalk.bold(title)} `;
  const side = width - titleTxt.length > 8 ? '─'.repeat(Math.floor((width - titleTxt.length) / 2)) : '─'.repeat(2);
  console.log('\n' + chalk.cyan(side) + titleTxt + chalk.cyan(side) + '\n');
}

export function badge(text: string, color: Color, fill = ' '): string {
  const padded = `${fill}${text}${fill}`;
  const colored = fg(color)(padded);
  const dim = chalk.dim('|');
  return `${dim}${colored}${dim}`;
}

export function box(lines: string[], opts: { title?: string; color?: Color } = {}): string {
  const lw = process.stdout.columns ? Math.min(process.stdout.columns - 4, 100) : 80;
  const out: string[] = [];
  const topChar = '━';
  const bChar = chalk[opts.color ?? 'cyan'] as (s: string) => string;
  const shrink = lines.map((l) => (l.length > lw ? l.slice(0, lw - 1) + '…' : l.padEnd(lw)));
  const titlePad = opts.title ? ` ${opts.title} ` : '';
  out.push(bChar(`┏${topChar.repeat(lw - 2 - titlePad.length)}┓`));
  for (const l of shrink) out.push(bChar('┃') + l + bChar('┃'));
  out.push(bChar(`┗${topChar.repeat(lw - 2)}┛`));
  return out.join('\n');
}

export function ok(message: string): void {
  console.log(chalk.green('✔ ') + chalk.green(message));
}

export function warn(message: string): void {
  console.log(chalk.yellow('⚠ ') + chalk.yellow(message));
}

export function info(message: string): void {
  console.log(chalk.cyan('ℹ ') + chalk.cyan(message));
}

export function fail(message: string): void {
  console.log(chalk.red('✖ ') + chalk.red(message));
}

export function dim(message: string): void {
  console.log(chalk.dim(message));
}

/**
 * Spinner / loader helper. Animated in TTY, prints one-shot feedback elsewhere.
 */
export async function withSpinner<T>(
  text: string,
  fn: () => T | Promise<T>,
  opts: { doneText?: string; ms?: number } = {},
): Promise<T> {
  const { default: ora } = await import('ora');
  const spinner = ora({ text, color: 'cyan' }).start();
  try {
    if (opts.ms) await delay(opts.ms);
    const result = await fn();
    spinner.succeed(opts.doneText ?? text);
    return result;
  } catch (err) {
    spinner.fail((err as Error).message);
    throw err;
  }
}

export function progressBar(ratio: number, width = 20): string {
  const clamped = Math.max(0, Math.min(1, ratio));
  const filled = Math.round(clamped * width);
  const pct = Math.round(clamped * 100);
  const blocks = '█'.repeat(filled) + '░'.repeat(width - filled);
  const color = pct < 34 ? chalk.red : pct < 67 ? chalk.yellow : chalk.green;
  return `${color(blocks)} ${String(pct).padStart(3)}%`;
}

export function truncate(text: string, max: number): string {
  if (text.length <= max) return text;
  return text.slice(0, max - 1) + '…';
}