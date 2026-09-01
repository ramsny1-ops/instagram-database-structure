/*
 * ============================================================
 * PROGRAM: Array Basics - Reading, Printing & Summing Elements
 * ============================================================
 * TOPIC: Arrays, Loops, Basic I/O
 * LEVEL: Beginner
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * A teacher has recorded the exam scores of 30 students in a class.
 * They store all scores in an array. They need to:
 *   - Store all the marks
 *   - Display all the marks
 *   - Calculate the total marks and average
 * This is the most fundamental use of arrays - storing a collection
 * of related data items under a single variable name.
 *
 * WORD PROBLEM:
 * ------------
 * "A shopkeeper records daily sales for a week (7 days) in an array.
 *  The sales are: $120, $200, $150, $300, $250, $180, $220.
 *  Write a program to store these values in an array and display
 *  them along with the total weekly sales and average daily sales."
 *
 * WHAT IS AN ARRAY?
 * ----------------
 * An array is a collection of elements of the same data type stored
 * in contiguous memory locations. Think of it as a row of pigeonholes
 * where each hole holds one value, and each hole has an index (starting 0).
 *
 * KEY CONCEPTS:
 * ------------
 *   - Declaration:  int arr[5];        // array of 5 integers
 *   - Access:       arr[0], arr[1], ...  // index starts at 0!
 *   - Size:         sizeof(arr)/sizeof(arr[0]) gives element count
 *   - Memory:       All elements stored in consecutive memory addresses
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Array index ALWAYS starts at 0, not 1!
 *      arr[5] of size 5 accesses indices 0,1,2,3,4
 *   2. Use sizeof(arr)/sizeof(arr[0]) to get array length
 *      This prevents bugs when array size changes
 *   3. Always validate array index to avoid buffer overflow
 *   4. Use symbolic constants (#define or const) for array sizes
 *   5. Initialize arrays to zero if needed: int arr[5] = {0};
 *   6. Partial initialization: int arr[5] = {1,2} fills rest with 0
 *   7. You can omit the size if you provide initializers: int arr[] = {1,2,3}
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Declare array of size N and variables for sum, i
 *   3. Prompt user to enter N elements
 *   4. Use a FOR loop to read each element into the array
 *   5. Use another FOR loop to print each element
 *   6. Accumulate sum during the print loop (or a third loop)
 *   7. Calculate and display average
 *   8. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(n) - single pass through array
 *   Space Complexity: O(n) - array of n elements
 * ============================================================
 */

#include <stdio.h>

#define MAX_SIZE 100  // Maximum array size - easy to change

int main() {
    int arr[MAX_SIZE];
    int n, i, sum;
    float average;

    printf("============================================\n");
    printf("       ARRAY BASICS - READ & DISPLAY\n");
    printf("============================================\n\n");

    // ---- GET ARRAY SIZE ----
    printf("How many elements do you want to store? (max %d): ", MAX_SIZE);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("[ERROR] Invalid size! Must be between 1 and %d.\n", MAX_SIZE);
        return 1;
    }

    // ---- READ ARRAY ELEMENTS ----
    printf("\n--- Enter %d elements ---\n", n);
    for (i = 0; i < n; i++) {
        printf("Element[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    // ---- DISPLAY ARRAY ELEMENTS ----
    printf("\n--- Array Elements ---\n");
    printf("Index | Value\n");
    printf("------|------\n");
    for (i = 0; i < n; i++) {
        printf("  %2d  |  %d\n", i, arr[i]);
    }

    // ---- CALCULATE SUM AND AVERAGE ----
    sum = 0;
    for (i = 0; i < n; i++) {
        sum += arr[i];  // sum = sum + arr[i]
    }
    average = (float)sum / n;  // Cast to float for decimal result

    // ---- DISPLAY SUMMARY ----
    printf("\n--- Summary ---\n");
    printf("Number of elements:  %d\n", n);
    printf("Total sum:           %d\n", sum);
    printf("Average:             %.2f\n", average);
    printf("Maximum element:     %d\n", arr[0]);  // placeholder, see tip below
    printf("Minimum element:     %d\n", arr[0]);

    // ---- TIP: Finding min/max in same loop ----
    int max = arr[0], min = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    printf("Maximum element:     %d\n", max);
    printf("Minimum element:     %d\n", min);

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Application: Sales Data ---\n");
    printf("If these represent daily sales ($), total weekly revenue: $%d\n", sum);
    printf("Average daily revenue: $%.2f\n", average);

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 04_array_basics.c -o array_basics
 *
 * SAMPLE INPUT: 5 elements -> 10, 20, 30, 40, 50
 * SAMPLE OUTPUT: Sum=150, Average=30.00
 *
 * TIP: Arrays are the building blocks for more complex data structures
 * like stacks, queues, hash tables, and matrices.
 */