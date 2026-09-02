import { randomUUID } from 'node:crypto';

export function id(prefix = ''): string {
  return `${prefix}${randomUUID().slice(0, 8)}`;
}