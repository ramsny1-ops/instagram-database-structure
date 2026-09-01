/*
 * ============================================================
 * PROGRAM: Pattern Printing - Triangle Patterns
 * ============================================================
 * TOPIC: Nested Loops, Pattern Recognition
 * LEVEL: Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Pattern printing develops logical thinking and nested loop
 * mastery. These concepts translate to:
 *   - Matrix/grid generation (games, spreadsheets)
 *   - ASCII art generation
 *   - User interface layout engines
 *   - Image pixel manipulation
 *   - Generating test data for algorithms
 *
 * WORD PROBLEM:
 * ------------
 * "Design a seating chart for an auditorium where rows have
 *  increasing seats: Row 1 has 1 seat, Row 2 has 3 seats,
 *  Row 3 has 5 seats, etc. (Pattern: 1, 3, 5, 7, 9...)"
 *
 * PATTERNS COVERED:
 * ------------------
 *   1. Right-angled triangle (numbers)
 *   2. Inverted right-angled triangle
 *   3. Full pyramid (centered)
 *   4. Diamond pattern
 *   5. Number pyramid
 *   6. Butterfly pattern
 *
 * TIPS & TRICKS:
 * -------------
 *   1. EVERY pattern can be broken into: SPACES and STARS (*)
 *   2. Count spaces per row: (total_rows - current_row)
 *   3. Count stars per row: (2 * current_row - 1) for pyramid
 *   4. Nested loops: Outer = rows, Inner = columns (spaces + stars)
 *   5. For number patterns, use a counter variable that increments
 *   6. Think in terms of coordinates: for each (row, col), what should print?
 *   7. Start with the simplest pattern and build complexity
 *
 * LOGIC FLOW (Pyramid Example):
 * -------------------------------
 *   1. Start
 *   2. Read number of rows
 *   3. For each row i (1 to n):
 *      a. Print (n-i) spaces
 *      b. Print (2i-1) stars
 *      c. Move to next line
 *   4. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(n²) - nested loops
 *   Space Complexity: O(1)
 * ============================================================
 */

#include <stdio.h>

/*
 * Right-Angled Triangle (Numbers)
 * Row 1: 1
 * Row 2: 1 2
 * Row 3: 1 2 3
 */
void rightAngledTriangle(int n) {
    printf("\n--- Right-Angled Triangle (Numbers) ---\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
}

/*
 * Inverted Right-Angled Triangle (Stars)
 * Row 1: *****  (n stars)
 * Row 2: ****   (n-1 stars)
 * Row 3: ***    (n-2 stars)
 */
void invertedTriangle(int n) {
    printf("\n--- Inverted Triangle (Stars) ---\n");
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
}

/*
 * Full Pyramid (Stars)
 *     *
 *    ***
 *   *****
 *  *******
 */
void pyramid(int n) {
    printf("\n--- Pyramid Pattern (Stars) ---\n");
    for (int i = 1; i <= n; i++) {
        // Print leading spaces
        for (int j = 1; j <= n - i; j++) {
            printf("  ");
        }
        // Print stars
        for (int j = 1; j <= 2 * i - 1; j++) {
            printf("* ");
        }
        printf("\n");
    }
}

/*
 * Number Pyramid
 *     1
 *    2 3 2
 *   3 4 5 4 3
 *  4 5 6 7 6 5 4
 */
void numberPyramid(int n) {
    printf("\n--- Number Pyramid ---\n");
    for (int i = 1; i <= n; i++) {
        // Leading spaces
        for (int j = 1; j <= n - i; j++) {
            printf("  ");
        }
        // Left ascending
        for (int j = i; j >= 1; j--) {
            printf("%d ", j);
        }
        // Right ascending
        for (int j = 2; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
}

/*
 * Diamond Pattern
 *    *
 *   ***
 *  *****
 * *******
 *  *****
 *   ***
 *    *
 */
void diamond(int n) {
    printf("\n--- Diamond Pattern ---\n");
    // Upper half including middle
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) printf("  ");
        for (int j = 1; j <= 2 * i - 1; j++) printf("* ");
        printf("\n");
    }
    // Lower half
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++) printf("  ");
        for (int j = 1; j <= 2 * i - 1; j++) printf("* ");
        printf("\n");
    }
}

/*
 * Butterfly Pattern
 * *                       *
 * **                     **
 * ***                   ***
 * ****                 ****
 * *************** ***************
 */
void butterfly(int n) {
    printf("\n--- Butterfly Pattern ---\n");
    // Upper half
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) printf("* ");
        for (int j = 1; j <= 2 * (n - i); j++) printf("  ");
        for (int j = 1; j <= i; j++) printf("* ");
        printf("\n");
    }
    // Lower half
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) printf("* ");
        for (int j = 1; j <= 2 * (n - i); j++) printf("  ");
        for (int j = 1; j <= i; j++) printf("* ");
        printf("\n");
    }
}

int main() {
    int n;

    printf("============================================\n");
    printf("     PATTERN PRINTING PROGRAM\n");
    printf("  (Triangle, Pyramid, Diamond, Butterfly)\n");
    printf("============================================\n\n");

    printf("Enter the number of rows: ");
    scanf("%d", &n);

    if (n < 1 || n > 20) {
        printf("[ERROR] Please enter a value between 1 and 20.\n");
        return 1;
    }

    // ---- ALL PATTERNS ----
    rightAngledTriangle(n);
    invertedTriangle(n);
    pyramid(n);
    numberPyramid(n);
    diamond(n);
    butterfly(n);

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("• Game development: Tile maps, grid layouts\n");
    printf("• UI design: Understanding spacing and alignment\n");
    printf("• Image processing: Pixel pattern generation\n");
    printf("• Algorithm practice: Nested loop mastery\n");
    printf("• Teaching tool: Visual proof of loop invariants\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 14_pattern_triangle.c -o pattern
 *
 * SAMPLE INPUT: 5
 * SAMPLE OUTPUT: All 6 pattern types
 *
 * TRICK: The key to all patterns is:
 *        1. Identify the loop structure (outer=rows, inner=columns)
 *        2. Determine what prints at each (row, col) coordinate
 *        3. Separate logic into: spaces, content, newlines
 *        4. Practice with different symbols: *, #, $, numbers, letters
 */