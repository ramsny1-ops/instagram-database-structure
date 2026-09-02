import { Status, Priority, STATUS_LABEL, PRIORITY_LABEL } from './types.js';
import { statusColor, priorityColor } from './charts.js';

export function statusBadge(status: Status, plain = false): string {
  const txt = ` ${STATUS_LABEL[status]} `;
  return plain ? `|${txt}|` : `|${statusColor(status)(txt)}|`;
}

export function priorityBadge(priority: Priority, plain = false): string {
  const txt = ` ${PRIORITY_LABEL[priority]} `;
  return plain ? `|${txt}|` : `|${priorityColor(priority)(txt)}|`;
}

export function progressPlain(ratio: number): string {
  const clamped = Math.max(0, Math.min(1, ratio));
  const pct = Math.round(clamped * 100);
  return `${String(pct).padStart(3)}%`;
}