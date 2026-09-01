/*
 * ============================================================
 * PROGRAM: File Operations (Read, Write, Append, Copy)
 * ============================================================
 * TOPIC: File I/O, Pointers, Error Handling
 * LEVEL: Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * File operations are essential for:
 *   - Data persistence (saving user data between program runs)
 *   - Log files (recording system events)
 *   - Configuration files (storing app settings)
 *   - Data export/import (CSV, JSON, XML files)
 *   - Database storage (flat file databases)
 *   - Report generation (writing formatted output to files)
 *
 * WORD PROBLEM:
 * ------------
 * "A school needs to store student marks in a file. The program should:
 *  (a) Create a file and write student records,
 *  (b) Read the file and display all records,
 *  (c) Calculate and display the average,
 *  (d) Create a backup copy of the file."
 *
 * FILE I/O FUNCTIONS:
 * ---------------------
 *   FILE *fopen(const char *filename, const char *mode)
 *     Modes: "r" (read), "w" (write/truncate), "a" (append),
 *            "r+" (read+write), "w+" (read+write/create), "a+" (append+read)
 *
 *   char *fgets(char *str, int n, FILE *fp)
 *   int fprintf(FILE *fp, const char *format, ...)
 *   int fscanf(FILE *fp, const char *format, ...)
 *   int fputs(const char *str, FILE *fp)
 *   int fclose(FILE *fp)
 *   long ftell(FILE *fp) - get current position
 *   void rewind(FILE *fp) - reset to beginning
 *
 * TIPS & TRICKS:
 * -------------
 *   1. ALWAYS check if fopen() returns NULL (file doesn't exist, permission denied)
 *   2. Use "w" mode carefully - it TRUNCATES the file (deletes existing content!)
 *   3. Use "a" mode to append without destroying existing data
 *   4. Always fclose() when done to flush buffers and free resources
 *   5. Use feof() to check for end-of-file in reading loops
 *   6. Use ferror() to detect read/write errors
 *   7. Text files use \n; on Windows, it's converted to \r\n internally
 *   8. Binary files use "rb"/"wb" modes for exact byte-level access
 *   9. Buffer flushing: fflush() forces write to disk immediately
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Display menu (Write, Read, Append, Copy, Exit)
 *   3. Based on choice:
 *      a. Write: fopen("w"), write data, fclose
 *      b. Read: fopen("r"), read data, fclose
 *      c. Append: fopen("a"), append data, fclose
 *      d. Copy: open source, create destination, copy contents
 *   4. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(n) where n = file size
 *   Space Complexity: O(1) - reading/writing line by line
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

#define FILENAME "student_records.txt"
#define BACKUP_FILE "student_records_backup.txt"
#define MAX_LINE 256

/*
 * Write student records to a file
 * Each record: Name, Roll Number, Marks
 */
void writeToFile() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("[ERROR] Cannot create file!\n");
        return;
    }

    int n;
    printf("How many student records to write? ");
    scanf("%d", &n);
    while (getchar() != '\n');  // Clear input buffer

    fprintf(fp, "=== STUDENT RECORDS ===\n");
    fprintf(fp, "Name,Roll,Marks\n");

    for (int i = 0; i < n; i++) {
        char name[100];
        int roll, marks;

        printf("Student %d - Name: ", i + 1);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';  // Remove newline

        printf("         Roll Number: ");
        scanf("%d", &roll);
        printf("         Marks: ");
        scanf("%d", &marks);
        while (getchar() != '\n');

        fprintf(fp, "%s,%d,%d\n", name, roll, marks);
    }

    fclose(fp);
    printf("[SUCCESS] %d records written to '%s'\n", n, FILENAME);
}

/*
 * Read and display all records from the file
 */
void readFromFile() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("[ERROR] File not found! Please write records first.\n");
        return;
    }

    char line[MAX_LINE];
    int lineCount = 0;
    int totalMarks = 0, count = 0;

    printf("\n--- File Contents of '%s' ---\n", FILENAME);
    printf("%-25s %-10s %-10s\n", "Name", "Roll", "Marks");
    printf("------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline
        printf("%-25s %-10s %-10s\n", line, "", "");

        // Parse marks from CSV line (last field)
        if (count > 0 && count <= 10) {  // Skip header lines
            char *token = strtok(line, ",");
            int field = 0;
            int marks = 0;
            while (token != NULL) {
                if (field == 2) marks = atoi(token);
                token = strtok(NULL, ",");
                field++;
            }
            if (count <= 10 && count > 0) {  // Only count valid records
                totalMarks += marks;
                count++;
            }
        }
        lineCount++;
    }

    if (lineCount > 2) {
        printf("\nTotal records: %d\n", lineCount - 2);
        printf("Average marks: %.2f\n", (float)totalMarks / (lineCount - 2));
    }

    fclose(fp);
}

/*
 * Append a new record to the file
 */
void appendToFile() {
    FILE *fp = fopen(FILENAME, "a");
    if (fp == NULL) {
        printf("[ERROR] File not found!\n");
        return;
    }

    char name[100];
    int roll, marks;

    printf("Enter student Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter Roll Number: ");
    scanf("%d", &roll);
    printf("Enter Marks: ");
    scanf("%d", &marks);

    fprintf(fp, "%s,%d,%d\n", name, roll, marks);
    fclose(fp);
    printf("[SUCCESS] Record appended to '%s'\n", FILENAME);
}

/*
 * Copy a file to a backup location
 * @param source: source filename
 * @param dest: destination filename
 */
void copyFile(const char *source, const char *dest) {
    FILE *src = fopen(source, "r");
    if (src == NULL) {
        printf("[ERROR] Source file not found!\n");
        return;
    }

    FILE *dst = fopen(dest, "w");
    if (dst == NULL) {
        printf("[ERROR] Cannot create destination file!\n");
        fclose(src);
        return;
    }

    char line[MAX_LINE];
    int linesCopied = 0;

    while (fgets(line, sizeof(line), src) != NULL) {
        fputs(line, dst);
        linesCopied++;
    }

    fclose(src);
    fclose(dst);
    printf("[SUCCESS] Copied %d lines from '%s' to '%s'\n",
           linesCopied, source, dest);
}

int main() {
    int choice;

    printf("============================================\n");
    printf("       FILE OPERATIONS PROGRAM\n");
    printf("============================================\n");

    while (1) {
        printf("\n--- File Operations Menu ---\n");
        printf("  1. Write records to file\n");
        printf("  2. Read records from file\n");
        printf("  3. Append a record\n");
        printf("  4. Create backup copy\n");
        printf("  0. Exit\n");
        printf("  Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: writeToFile(); break;
            case 2: readFromFile(); break;
            case 3: appendToFile(); break;
            case 4: copyFile(FILENAME, BACKUP_FILE); break;
            case 0:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("[ERROR] Invalid choice!\n");
        }
    }

    return 0;
}
/*
 * COMPILATION:
 *   gcc 18_file_operations.c -o file_ops
 *
 * SAMPLE USAGE:
 *   Write: Add 3 student records
 *   Read: Display all records with average
 *   Copy: Create a backup file
 *
 * TRICK: Always use fclose() to flush buffers. Without it,
 *        data may remain in the buffer and not be written to disk,
 *        causing data loss if the program crashes before exit.
 *        Use fflush(fp) as a safety measure for critical writes.
 */