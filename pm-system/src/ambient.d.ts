/**
 * Minimal ambient type declarations for `cli-table3`, which does not ship
 * its own types and is missing from the type registry this project uses.
 */
declare module 'cli-table3' {
  export interface TableInstance {
    push(...rows: Array<Array<string | number | Record<string, unknown>>>): number;
    toString(): string;
  }

  export interface TableOptions {
    head?: string[];
    style?: {
      head?: string[];
      border?: string[];
      'padding-left'?: number;
      'padding-right'?: number;
    };
    chars?: {
      top?: string;
      'top-mid'?: string;
      'top-left'?: string;
      'top-right'?: string;
      bottom?: string;
      'bottom-mid'?: string;
      'bottom-left'?: string;
      'bottom-right'?: string;
      left?: string;
      'left-mid'?: string;
      mid?: string;
      'mid-mid'?: string;
      right?: string;
      'right-mid'?: string;
      middle?: string;
    };
    colWidths?: number[];
    wordWrap?: boolean;
  }

  export default class Table {
    constructor(options?: TableOptions);
    push(...rows: Array<Array<string | number | Record<string, unknown>>>): number;
    toString(): string;
  }
}