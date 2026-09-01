/*
 * ============================================================
 * PROGRAM: Linear Search in an Array
 * ============================================================
 * TOPIC: Arrays, Searching Algorithms
 * LEVEL: Beginner
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * A university maintains a list of student roll numbers in an array.
 * When a student wants to check their grade, the system searches
 * through the roll number list to find their record. Linear search
 * is the simplest searching technique - check each element one by one.
 *
 * WORD PROBLEM:
 * ------------
 * "A librarian has books numbered 101, 205, 307, 410, 555 on a shelf.
 *  A student asks for book number 307. Starting from the left, the
 *  librarian checks each book number until the desired one is found.
 *  At which position is the book found?"
 *
 * ALGORITHM - LINEAR SEARCH:
 * --------------------------
 *   1. Start from the first element (index 0)
 *   2. Compare the current element with the target value
 *   3. If they match, return the index (position found!)
 *   4. If they don't match, move to the next element
 *   5. If all elements are checked and no match is found, return -1
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Linear search works on BOTH sorted and unsorted arrays
 *   2. Time complexity is O(n) in worst case - must check every element
 *   3. Best case is O(1) - if the target is the first element
 *   4. You can optimize slightly by searching from both ends simultaneously
 *   5. For sorted arrays, consider BINARY SEARCH (O(log n)) instead
 *   6. Use a sentinel value (-1) to indicate "not found"
 *   7. Store the position (index + 1) for human-readable output
 *   8. If duplicates exist, linear search finds the FIRST occurrence
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Declare array, get size and elements from user
 *   3. Get the search key from user
 *   4. Loop through each element:
 *      a. If arr[i] == key, store position and break
 *   5. If found, display position (1-based index)
 *   6. If not found, display "not found" message
 *   7. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:
 *     - Best Case:    O(1) - element found at first position
 *     - Worst Case:   O(n) - element at last position or not present
 *     - Average Case: O(n) - element somewhere in middle
 *   Space Complexity: O(1) - no extra space needed
 * ============================================================
 */

#include <stdio.h>

#define MAX_SIZE 100

/*
 * Linear Search Function
 * Searches for 'key' in array 'arr' of size 'n'
 * @param arr: the array to search in
 * @param n: size of the array
 * @param key: the value to search for
 * @return: index of the element if found, -1 otherwise
 */
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;  // Return the index where key was found
        }
    }
    return -1;  // Key not found in the array
}

int main() {
    int arr[MAX_SIZE];
    int n, key, result;

    printf("============================================\n");
    printf("       LINEAR SEARCH IN AN ARRAY\n");
    printf("============================================\n\n");

    // ---- INPUT ARRAY SIZE ----
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("[ERROR] Invalid size!\n");
        return 1;
    }

    // ---- INPUT ARRAY ELEMENTS ----
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Element[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    // ---- DISPLAY ARRAY ----
    printf("\nArray contents: { ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("}\n");

    // ---- GET SEARCH KEY ----
    printf("\nEnter the number you want to search for: ");
    scanf("%d", &key);

    // ---- PERFORM SEARCH ----
    result = linearSearch(arr, n, key);

    // ---- DISPLAY RESULT ----
    printf("\n--- Search Result ---\n");
    if (result != -1) {
        printf("[FOUND] %d is at index %d (position %d)\n",
               key, result, result + 1);
        printf("\nTip: Index %d means it's the %dth element.\n",
               result, result + 1);
    } else {
        printf("[NOT FOUND] %d is not in the array.\n", key);
        printf("Tip: Linear search checked all %d elements.\n", n);
    }

    // ---- ADDITIONAL: Count occurrences ----
    printf("\n--- Additional Info ---\n");
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) count++;
    }
    if (count > 0) {
        printf("'%d' appears %d time(s) in the array.\n", key, count);
        printf("Positions: ");
        for (int i = 0; i < n; i++) {
            if (arr[i] == key) printf("%d ", i);
        }
        printf("\n");
    }

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Application ---\n");
    printf("Imagine this as student roll numbers.\n");
    printf("If searching for roll number %d:\n", key);
    if (result != -1) {
        printf("Student found! Retrieve their record from shelf position %d.\n",
               result + 1);
    } else {
        printf("No student with this roll number exists.\n");
    }

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 05_array_search.c -o array_search
 *
 * SAMPLE INPUT:
 *   Elements: 10 20 30 40 50
 *   Search for: 30
 * SAMPLE OUTPUT:
 *   [FOUND] 30 is at index 2 (position 3)
 */