/*
 * ============================================================
 * PROGRAM: Ascending & Descending Order of Array
 * ============================================================
 * TOPIC: Arrays, Sorting (Bubble Sort variations)
 * LEVEL: Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * A school needs to display student marks in two ways:
 *   - Ascending: to show students who need the most improvement
 *   - Descending: to show toppers at the top
 *   The same array can be sorted both ways. Understanding how to
 *   switch between ascending and descending order is crucial for
 *   any data presentation system.
 *
 * WORD PROBLEM:
 * ------------
 * "A race has 6 runners with finish times (in seconds): 45, 32, 38, 29, 51, 35.
 *  The winner is the one with the LOWEST time. Sort in ascending order to
 *  show the ranking. Then sort in descending order to show who took the
 *  longest."
 *
 * ASCENDING vs DESCENDING:
 * ------------------------
 *   Ascending: Smallest to Largest  (or First to Last)
 *     Comparison: if arr[j] > arr[j+1] → swap
 *   Descending: Largest to Smallest (or Last to First)
 *     Comparison: if arr[j] < arr[j+1] → swap
 *
 *   The ONLY difference is the comparison operator!
 *   > for ascending, < for descending.
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Both ascending and descending use the same bubble sort structure
 *   2. Change ONLY the comparison operator: > vs <
 *   3. You can also write a generic sort function with a comparator
 *   4. For descending, after sorting, arr[0] is the MAXIMUM and arr[n-1] is MINIMUM
 *   5. Think of it like sorting a deck: ascending = ace to king, descending = king to ace
 *   6. You can also achieve descending by sorting ascending then reversing
 *   7. Bubble sort is O(n²) - for production code, use qsort() from <stdlib.h>
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read array size and elements
 *   3. Display original array
 *   4. Sort a COPY in ascending order using bubble sort
 *   5. Sort the ORIGINAL in descending order using bubble sort
 *   6. Display both results
 *   7. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity: O(n²) for each sort (two sorts = still O(n²))
 *   Space Complexity: O(n) for the copy, O(1) for sorting itself
 * ============================================================
 */

#include <stdio.h>
#include <string.h>  // For memcpy

#define MAX_SIZE 100

/*
 * Bubble Sort with order parameter
 * @param arr: array to sort
 * @param n: size of array
 * @param ascending: 1 for ascending, 0 for descending
 */
void bubbleSort(int arr[], int n, int ascending) {
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {
            int shouldSwap;

            if (ascending) {
                shouldSwap = (arr[j] > arr[j + 1]);  // Ascending: swap if out of order (>)
            } else {
                shouldSwap = (arr[j] < arr[j + 1]);  // Descending: swap if out of order (<)
            }

            if (shouldSwap) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped) break;  // Early termination
    }
}

/*
 * Print array
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
    int arrCopy[MAX_SIZE];  // Copy for independent sorting
    int n;

    printf("============================================\n");
    printf("  ASCENDING & DESCENDING ORDER OF ARRAY\n");
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

    // ---- SORT ASCENDING ----
    memcpy(arrCopy, arr, n * sizeof(int));  // Make a copy
    bubbleSort(arrCopy, n, 1);  // 1 = ascending

    printf("\n--- Sorted Ascending (Smallest → Largest) ---\n");
    printArray(arrCopy, n);
    printf("\n");
    printf("First (min): %d\n", arrCopy[0]);
    printf("Last  (max): %d\n", arrCopy[n - 1]);

    // ---- SORT DESCENDING ----
    memcpy(arrCopy, arr, n * sizeof(int));  // Reset copy
    bubbleSort(arrCopy, n, 0);  // 0 = descending

    printf("\n--- Sorted Descending (Largest → Smallest) ---\n");
    printArray(arrCopy, n);
    printf("\n");
    printf("First (max): %d\n", arrCopy[0]);
    printf("Last  (min): %d\n", arrCopy[n - 1]);

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("Ascending:  Student scores (lowest to highest for review)\n");
    printf("Descending: Exam rankings (highest to lowest for toppers)\n");
    printf("Descending: Product prices (most expensive first)\n");
    printf("Ascending:  Search results by relevance score\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 08_ascending_descending.c -o order_array
 *
 * SAMPLE INPUT: 6 elements -> 45 32 38 29 51 35
 * SAMPLE OUTPUT:
 *   Ascending:  { 29 32 35 38 45 51 }
 *   Descending: { 51 45 38 35 32 29 }
 *
 * TIP: In real-world C, you'd use qsort() from <stdlib.h> for efficiency.
 *      But understanding bubble sort builds the foundation for all sorting.
 */