#!/usr/bin/env node
import { makeProgram, run } from './commands/common.js';
import { registerProjectCommands } from './commands/project.js';
import { registerMemberCommands } from './commands/member.js';
import { registerTaskCommands } from './commands/task.js';
import { registerStatsCommand } from './commands/stats.js';
import { registerGanttCommand } from './commands/gantt.js';
import { registerReportCommand } from './commands/report.js';
import { registerExportImport } from './commands/export.js';
import { registerDemoCommand } from './commands/demo.js';

const program = makeProgram();

registerProjectCommands(program);
registerMemberCommands(program);
registerTaskCommands(program);
registerStatsCommand(program);
registerGanttCommand(program);
registerReportCommand(program);
registerExportImport(program);
registerDemoCommand(program);

program.parse();