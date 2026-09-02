export type Status = 'todo' | 'in-progress' | 'review' | 'done';

export type Priority = 'low' | 'medium' | 'high' | 'critical';

export interface Comment {
  id: string;
  author: string;
  body: string;
  createdAt: string;
}

export interface TimeLog {
  id: string;
  hours: number;
  note: string;
  date: string;
}

export interface Task {
  id: string;
  title: string;
  description: string;
  status: Status;
  priority: Priority;
  tags: string[];
  assigneeId: string | null;
  dueDate: string | null;
  startDate: string | null;
  estimate: number;
  createdAt: string;
  comments: Comment[];
  timeLogs: TimeLog[];
}

export interface Project {
  id: string;
  name: string;
  description: string;
  createdAt: string;
  tasks: Task[];
}

export interface Member {
  id: string;
  name: string;
  role: string;
  createdAt: string;
}

export interface DB {
  version: number;
  createdAt: string;
  updatedAt: string;
  projects: Project[];
  members: Member[];
}

export const STATUSES: Status[] = ['todo', 'in-progress', 'review', 'done'];
export const PRIORITIES: Priority[] = ['low', 'medium', 'high', 'critical'];

export const STATUS_ORDER: Record<Status, number> = {
  todo: 0,
  'in-progress': 1,
  review: 2,
  done: 3,
};

export const STATUS_LABEL: Record<Status, string> = {
  todo: 'TODO',
  'in-progress': 'IN PROGRESS',
  review: 'REVIEW',
  done: 'DONE',
};

export const PRIORITY_LABEL: Record<Priority, string> = {
  low: 'LOW',
  medium: 'MEDIUM',
  high: 'HIGH',
  critical: 'CRITICAL',
};