/*
 * ============================================================
 * PROGRAM: Binary Search Algorithm
 * ============================================================
 * TOPIC: Searching Algorithms, Divide and Conquer
 * LEVEL: Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Binary search is used everywhere in software:
 *   - Dictionary apps: Open to the middle, eliminate half the book
 *   - Git bisect: Find which commit introduced a bug
 *   - Debugging: Binary search on commit history (git bisect)
 *   - Databases: Index lookups in B-trees
 *   - Operating systems: Page table lookups, memory allocation
 *   - Phone books: Finding a name by starting from the middle
 *
 * WORD PROBLEM:
 * ------------
 * "A sorted array of 1000 student IDs is given. A student with
 *  ID 5432 is looking for their record. Using binary search,
 *  what is the maximum number of comparisons needed to find
 *  the record? (Hint: log₂(1000) ≈ 10 comparisons)"
 *
 * BINARY SEARCH ALGORITHM:
 * --------------------------
 *   Given a SORTED array:
 *   1. Set low = 0, high = n-1
 *   2. While low <= high:
 *      a. mid = (low + high) / 2
 *      b. If arr[mid] == target: FOUND! Return mid
 *      c. If arr[mid] < target: target is in right half → low = mid + 1
 *      d. If arr[mid] > target: target is in left half → high = mid - 1
 *   3. If not found, return -1
 *
 * BINARY SEARCH vs LINEAR SEARCH:
 * ----------------------------------
 *   Linear Search: O(n) - check every element
 *   Binary Search: O(log n) - eliminate half each time!
 *
 *   For 1,000,000 elements:
 *   - Linear search: up to 1,000,000 comparisons
 *   - Binary search: at most 20 comparisons! (log₂(1,000,000) ≈ 20)
 *
 * ITERATIVE vs RECURSIVE:
 * --------------------------
 *   Iterative: Uses a while loop, O(1) space
 *   Recursive: Uses function calls, O(log n) space (call stack)
 *
 * TIPS & TRICKS:
 * -------------
 *   1. BINARY SEARCH REQUIRES A SORTED ARRAY - precondition!
 *   2. mid = low + (high - low) / 2 avoids integer overflow
 *      compared to mid = (low + high) / 2
 *   3. For sorted arrays, always prefer binary search over linear
 *   4. The array must be sorted in the SAME order as the search
 *      (ascending search needs ascending-sorted array)
 *   5. Use lower_bound and upper_bound for finding first/last occurrence
 *   6. Binary search can be applied on answer space (binary search on answer)
 *   7. Time complexity: O(log n) - incredibly efficient!
 *   8. Can be extended to 2D matrices, rotated sorted arrays, etc.
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read sorted array size and elements
 *   3. Read the target value to search for
 *   4. Set low = 0, high = n-1
 *   5. While low <= high:
 *      a. Calculate mid = low + (high - low) / 2
 *      b. If arr[mid] == target: return mid
 *      c. If target > arr[mid]: low = mid + 1
 *      d. Else: high = mid - 1
 *   6. If loop ends, target not found
 *   7. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:
 *     - Best:     O(1) - target at middle
 *     - Average:  O(log n)
 *     - Worst:    O(log n)
 *   Space Complexity:
 *     - Iterative: O(1)
 *     - Recursive: O(log n)
 * ============================================================
 */

#include <stdio.h>

/*
 * Iterative Binary Search
 * @param arr: sorted array
 * @param n: size of array
 * @param target: value to search for
 * @return: index of target if found, -1 otherwise
 */
int binarySearch(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;
    int comparisons = 0;

    while (low <= high) {
        // Safe midpoint calculation (avoids integer overflow)
        int mid = low + (high - low) / 2;
        comparisons++;

        if (arr[mid] == target) {
            printf("[Info] Found in %d comparison(s).\n", comparisons);
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;  // Search right half
        } else {
            high = mid - 1;  // Search left half
        }
    }

    printf("[Info] Searched %d comparison(s).\n", comparisons);
    return -1;  // Not found
}

/*
 * Recursive Binary Search Helper
 * @param arr: sorted array
 * @param low: lower bound index
 * @param high: upper bound index
 * @param target: value to search for
 * @param comparisons: pointer to comparison counter
 * @return: index if found, -1 otherwise
 */
int binarySearchRecursive(int arr[], int low, int high, int target, int *comparisons) {
    if (low > high) return -1;

    (*comparisons)++;
    int mid = low + (high - low) / 2;

    if (arr[mid] == target) return mid;
    if (arr[mid] < target)
        return binarySearchRecursive(arr, mid + 1, high, target, comparisons);
    else
        return binarySearchRecursive(arr, low, mid - 1, target, comparisons);
}

/*
 * Find first occurrence of target in sorted array (with duplicates)
 * @param arr: sorted array
 * @param n: size of array
 * @param target: value to find
 * @return: index of first occurrence, -1 if not found
 */
int findFirstOccurrence(int arr[], int n, int target) {
    int low = 0, high = n - 1, result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = mid;
            high = mid - 1;  // Continue searching in left half
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

/*
 * Find last occurrence of target in sorted array (with duplicates)
 * @param arr: sorted array
 * @param n: size of array
 * @param target: value to find
 * @return: index of last occurrence, -1 if not found
 */
int findLastOccurrence(int arr[], int n, int target) {
    int low = 0, high = n - 1, result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = mid;
            low = mid + 1;  // Continue searching in right half
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

void printArray(int arr[], int n) {
    printf("{ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("}");
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 42, 51, 67, 74, 89, 95};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target;

    printf("============================================\n");
    printf("      BINARY SEARCH ALGORITHM\n");
    printf("============================================\n\n");

    printf("--- Sorted Array ---\n");
    printArray(arr, n);
    printf("\n");
    printf("Array size: %d elements\n", n);
    printf("Max comparisons needed: %d (log₂(%d) ≈ %d)\n",
           1, n, 1);
    int temp = n;
    int maxComp = 0;
    while (temp > 0) { temp /= 2; maxComp++; }
    printf("Max comparisons needed: %d (log₂(%d) ≈ %d)\n\n",
           maxComp, n, maxComp);

    printf("Enter the value to search for: ");
    scanf("%d", &target);

    // ---- ITERATIVE BINARY SEARCH ----
    printf("\n--- Iterative Binary Search ---\n");
    int result = binarySearch(arr, n, target);

    if (result != -1) {
        printf("[FOUND] %d at index %d (position %d)\n",
               target, result, result + 1);
    } else {
        printf("[NOT FOUND] %d is not in the array.\n", target);
    }

    // ---- RECURSIVE BINARY SEARCH ----
    printf("\n--- Recursive Binary Search ---\n");
    int comp = 0;
    int recResult = binarySearchRecursive(arr, 0, n - 1, target, &comp);

    if (recResult != -1) {
        printf("[FOUND] %d at index %d (position %d) in %d comparisons\n",
               target, recResult, recResult + 1, comp);
    } else {
        printf("[NOT FOUND] %d is not in the array (recursive).\n", target);
    }

    // ---- FIRST AND LAST OCCURRENCE ----
    printf("\n--- First & Last Occurrence (with duplicates) ---\n");
    int arr2[] = {1, 3, 5, 5, 5, 5, 7, 9, 11};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Array with duplicates: ");
    printArray(arr2, n2);
    printf("\n");

    printf("Searching for 5:\n");
    printf("First occurrence at index: %d\n", findFirstOccurrence(arr2, n2, 5));
    printf("Last occurrence at index:  %d\n", findLastOccurrence(arr2, n2, 5));
    printf("Total occurrences: %d\n",
           findLastOccurrence(arr2, n2, 5) - findFirstOccurrence(arr2, n2, 5) + 1);

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("• Dictionaries: Word lookup (open middle, eliminate half)\n");
    printf("• Git bisect: Binary search on commit history to find bugs\n");
    printf("• Databases: B-tree index lookups\n");
    printf("• Debugging: Binary search on problem space\n");
    printf("• Phone books: Finding names efficiently\n");
    printf("• Competitive programming: Binary search on answer\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 20_binary_search.c -o binary_search
 *
 * SAMPLE INPUT: 23
 * SAMPLE OUTPUT: [FOUND] 23 at index 5 (position 6)
 *
 * TRICK: Use mid = low + (high - low) / 2 instead of
 *        (low + high) / 2 to prevent integer overflow
 *        when low + high exceeds INT_MAX.
 */