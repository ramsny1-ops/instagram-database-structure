/*
 * ============================================================
 * PROGRAM: Array Sorting and Displaying
 * ============================================================
 * TOPIC: Arrays, Sorting, Bubble Sort
 * LEVEL: Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * An e-commerce website needs to display products sorted by price.
 * The prices are stored in an array. Bubble sort is the simplest
 * sorting algorithm - repeatedly step through the list, compare
 * adjacent elements, and swap them if they're in the wrong order.
 * Like bubbles rising in a soda, the largest elements "bubble up"
 * to the end of the array with each pass.
 *
 * WORD PROBLEM:
 * ------------
 * "Five students scored 85, 72, 93, 60, and 88 in an exam. Arrange
 *  their scores in ascending order to determine the ranking from
 *  lowest to highest."
 *
 * BUBBLE SORT ALGORITHM:
 * ----------------------
 *   For each pass i (from 0 to n-1):
 *     For each comparison j (from 0 to n-i-2):
 *       If arr[j] > arr[j+1], swap them
 *   After pass i, the last i elements are sorted
 *
 *   Visualization with [5, 3, 8, 4, 2]:
 *   Pass 1: [3, 5, 4, 2, 8]  <- 8 bubbled to end
 *   Pass 2: [3, 4, 2, 5, 8]  <- 5 bubbled to correct position
 *   Pass 3: [3, 2, 4, 5, 8]  <- 4 bubbled to correct position
 *   Pass 4: [2, 3, 4, 5, 8]  <- 3 bubbled to correct position
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Bubble sort makes n-1 passes for an array of size n
 *   2. After each pass i, the last i elements are already sorted
 *      So inner loop goes from 0 to n-i-2 (not n-1!)
 *   3. OPTIMIZATION: Add a flag to detect if no swaps occurred
 *      If no swaps in a pass, the array is already sorted -> break early!
 *   4. Bubble sort is STABLE (preserves relative order of equal elements)
 *   5. Time complexity: O(n²) worst/average case, O(n) best case (optimized)
 *   6. Not suitable for large datasets - use quicksort/mergesort instead
 *   7. Can sort in ascending or descending order by changing the
 *      comparison operator (swap if arr[j] > arr[j+1] for ascending,
 *      swap if arr[j] < arr[j+1] for descending)
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read array size and elements
 *   3. Display original array
 *   4. Perform bubble sort (ascending):
 *      a. Outer loop: i from 0 to n-2
 *      b. Inner loop: j from 0 to n-i-2
 *      c. If arr[j] > arr[j+1], swap them
 *   5. Display sorted array
 *   6. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:
 *     - Worst/Average: O(n²)
 *     - Best (optimized): O(n) when array is already sorted
 *   Space Complexity: O(1) - in-place sorting
 * ============================================================
 */

#include <stdio.h>

#define MAX_SIZE 100

/*
 * Bubble Sort Function (Ascending Order)
 * Optimized with early termination flag
 * @param arr: the array to sort
 * @param n: size of the array
 */
void bubbleSort(int arr[], int n) {
    int swapped;  // Flag to optimize: detect if any swap occurred

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;  // Reset flag at start of each pass

        // After each pass i, the last i elements are sorted
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // ---- SWAP arr[j] and arr[j+1] ----
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;  // A swap occurred
            }
        }

        // OPTIMIZATION: If no swaps, array is already sorted
        if (!swapped) {
            printf("[Optimization] Array sorted early after pass %d!\n", i + 1);
            break;
        }
    }
}

/*
 * Print array with formatting
 */
void printArray(int arr[], int n) {
    printf("{ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("}");
}

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("============================================\n");
    printf("     BUBBLE SORT - ARRAY SORTING PROGRAM\n");
    printf("============================================\n\n");

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("[ERROR] Invalid size!\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Element[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    printf("\n--- Original Array ---\n");
    printArray(arr, n);
    printf("\n");

    printf("\n--- Sorting Process ---\n");
    bubbleSort(arr, n);

    printf("\n--- Sorted Array (Ascending) ---\n");
    printArray(arr, n);
    printf("\n");

    // ---- DISPLAY SORTED DETAILS ----
    printf("\n--- Sorted Details ---\n");
    printf("Smallest element: %d (at position 1)\n", arr[0]);
    printf("Largest element:  %d (at position %d)\n", arr[n - 1], n);

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Application ---\n");
    printf("Use case: Ranking students by score (lowest to highest)\n");
    printf("Use case: Sorting products by price (cheapest first)\n");
    printf("Use case: Organizing contacts alphabetically (with strings)\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 07_array_sort_display.c -o bubble_sort
 *
 * SAMPLE INPUT: 5 elements -> 85 72 93 60 88
 * SAMPLE OUTPUT: { 60 72 85 88 93 }
 *
 * TIP: The key optimization is the 'swapped' flag. Without it,
 *      bubble sort always runs O(n²) even on sorted arrays.
 *      With it, sorted arrays complete in O(n) time.
 */