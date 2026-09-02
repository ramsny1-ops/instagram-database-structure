import { Status, Priority } from '../types.js';
import type { Color } from '../ui.js';

export function statusCellColor(s: Status): Color {
  switch (s) {
    case 'todo': return 'gray';
    case 'in-progress': return 'cyan';
    case 'review': return 'yellow';
    case 'done': return 'green';
    default: return 'white';
  }
}

export function priorityCellColor(p: Priority): Color {
  switch (p) {
    case 'low': return 'blue';
    case 'medium': return 'yellow';
    case 'high': return 'red';
    case 'critical': return 'magenta';
    default: return 'white';
  }
}