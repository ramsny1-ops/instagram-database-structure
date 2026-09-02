import chalk from 'chalk';
import { Task, Status, PRIORITIES, STATUSES } from './types.js';
import { todayIso } from './util.js';

type BarColor = 'red' | 'green' | 'yellow' | 'blue' | 'magenta' | 'cyan' | 'gray';

const FILLER = '█';
const EMPTY = '░';

function barOf(value: number, max: number, width: number, color: BarColor): string {
  const ratio = max === 0 ? 0 : value / max;
  const filled = Math.round(ratio * width);
  const blocks = FILLER.repeat(filled) + EMPTY.repeat(Math.max(0, width - filled));
  return chalk[color](blocks);
}

export function hbarChart(
  title: string,
  items: Array<{ label: string; value: number; color: BarColor }>,
  opts: { width?: number; suffix?: (v: number) => string } = {},
): string {
  const width = opts.width ?? 24;
  const max = Math.max(1, ...items.map((i) => i.value));
  const labelW = Math.max(...items.map((i) => i.label.length));
  const lines: string[] = [chalk.bold.cyan(title), ''];
  for (const item of items) {
    const label = item.label.padStart(labelW);
    const suffix = opts.suffix ? opts.suffix(item.value) : String(item.value);
    lines.push(`${label}  ${barOf(item.value, max, width, item.color)}  ${chalk.dim(suffix)}`);
  }
  return lines.join('\n');
}

export function legend(): string {
  const l = STATUSES.map((s) => `${statusColor(s)('■')} ${s}`).join('  ');
  return chalk.dim('Legend: ') + l;
}

export function statusColor(status: Status): (s: string) => string {
  switch (status) {
    case 'todo': return chalk.gray;
    case 'in-progress': return chalk.cyan;
    case 'review': return chalk.yellow;
    case 'done': return chalk.green;
    default: return chalk.white;
  }
}

export function priorityColor(p: string): (s: string) => string {
  switch (p) {
    case 'low': return chalk.blue;
    case 'medium': return chalk.yellow;
    case 'high': return chalk.red;
    case 'critical': return chalk.magenta;
    default: return chalk.white;
  }
}

export function ganttChart(tasks: Task[], memberName: (id: string | null) => string): string {
  const today = todayIso();
  const dated = tasks.filter((t) => t.startDate || t.dueDate);
  if (dated.length === 0) {
    return chalk.dim('No tasks with dates yet — maybe the Gantt is on vacation. 🏖');
  }

  const parsed = dated.map((t) => {
    const start = t.startDate ?? t.dueDate ?? today;
    const end = t.dueDate ?? t.startDate ?? today;
    return { t, start: start < end ? start : end, end: start < end ? end : start };
  });

  let minDay = parsed[0].start;
  let maxDay = parsed[0].end;
  for (const p of parsed) {
    if (p.start < minDay) minDay = p.start;
    if (p.end > maxDay) maxDay = p.end;
  }
  // give a little margin
  minDay = shift(minDay, -2);
  maxDay = shift(maxDay, 3);

  const spanMs = new Date(`${maxDay}T00:00:00`).getTime() - new Date(`${minDay}T00:00:00`).getTime();
  const spanDays = Math.max(1, Math.round(spanMs / 86400000));

  const MAX_COLS = Math.min(90, Math.max(20, (process.stdout.columns ?? 100) - 34));
  const step = Math.max(1, Math.ceil((spanDays + 1) / MAX_COLS));
  const cols = Math.ceil((spanDays + 1) / step);

  const dayIndex = (iso: string): number => {
    const ms = new Date(`${iso}T00:00:00`).getTime() - new Date(`${minDay}T00:00:00`).getTime();
    return Math.max(0, Math.round(ms / 86400000));
  };

  const todayIdx = dayIndex(today);

  // header: months line + day line
  let months = '';
  let days = '';
  let prevMonth = '';
  for (let c = 0; c < cols; c++) {
    const iso = shift(minDay, c * step);
    const m = iso.slice(5, 7);
    const monthName = MONTHS[Number(m) - 1];
    if (m !== prevMonth) months += monthName.slice(0, Math.min(3, step));
    else months += ' ';
    prevMonth = m;
    const dd = Number(iso.slice(8, 10));
    days += dd % 7 === 0 ? String(dd % 100).padStart(3, '.') : '...';
  }

  const out: string[] = [];
  out.push(chalk.bold.cyan('Gantt Chart'));
  out.push('');
  out.push(' ' + months);
  out.push(' ' + days);
  out.push(' ' + chalk.dim('─'.repeat(cols + 2)));

  for (const { t, start, end } of parsed) {
    const s = dayIndex(start);
    const e = dayIndex(end);
    const label = `${t.id} ${t.title}`;
    const truncated = label.length > 22 ? label.slice(0, 21) + '…' : label.padEnd(22);

    let bar = '';
    for (let c = 0; c < cols; c++) {
      const cStart = c * step;
      const cEnd = (c + 1) * step - 1;
      const overlaps = s <= cEnd && e >= cStart;
      if (!overlaps) {
        bar += ' ';
      } else {
        const isToday = todayIdx >= cStart && todayIdx <= cEnd;
        bar += isToday ? statusColor(t.status)('╳') : statusColor(t.status)(FILLER);
      }
    }
    const who = memberName(t.assigneeId);
    out.push(`${chalk.dim(truncated)} ${bar}`);
    void who;
  }
  out.push(' ' + chalk.dim('─'.repeat(cols + 2)));
  out.push(' ' + legend());
  return out.join('\n');
}

const MONTHS = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];

function shift(iso: string, days: number): string {
  const d = new Date(`${iso}T00:00:00`);
  d.setDate(d.getDate() + days);
  return d.toISOString().slice(0, 10);
}

export function statusSortRank(status: Status): number {
  return STATUSES.indexOf(status);
}

export function priorityRank(p: string): number {
  return PRIORITIES.indexOf(p as never);
}

export function topPriorities(): string[] {
  return PRIORITIES;
}