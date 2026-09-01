/*
 * ============================================================
 * PROGRAM: Reverse an Array
 * ============================================================
 * TOPIC: Arrays, Two-Pointer Technique, Swapping
 * LEVEL: Beginner
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * A stack of plates in a cafeteria is reversed when you flip it over.
 * Similarly, reversing an array means the first element becomes the
 * last and the last becomes the first. This is used in:
 *   - Undo functionality (reversing action history)
 *   - String manipulation (reversing text)
 *   - Data processing (reversing time-series data)
 *   - Image processing (flipping pixel arrays)
 *
 * WORD PROBLEM:
 * ------------
 * "An array contains the digits of a 5-digit number: [1, 2, 3, 4, 5].
 *  The number is 12345. After reversing the array, what number does
 *  it represent? How would you implement this in C?"
 *
 * TWO APPROACHES:
 * ---------------
 *   Method 1: Create a new array and fill it backwards
 *   Method 2: Swap elements in-place using two pointers (MORE EFFICIENT)
 *   We implement Method 2 (in-place swap) as it uses O(1) extra space.
 *
 * THE TWO-POINTER SWAP TECHNIQUE:
 * -------------------------------
 *   Left pointer  starts at index 0
 *   Right pointer starts at index n-1
 *   Swap arr[left] and arr[right]
 *   Move left forward (left++), right backward (right--)
 *   Continue until left >= right
 *
 * TIPS & TRICKS:
 * -------------
 *   1. You only need to iterate n/2 times (swap pairs)
 *   2. XOR swap can be used but is less readable and has UB issues
 *   3. Use a temporary variable for clean, safe swapping
 *   4. Alternatively, use arithmetic swap: a = a+b; b = a-b; a = a-b;
 *      But this can overflow! Stick with temp variable swap.
 *   5. The midpoint: for i from 0 to n/2 - 1, swap arr[i] and arr[n-1-i]
 *   6. For odd-length arrays, the middle element stays in place
 *   7. For even-length arrays, all elements get swapped
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read array size and elements
 *   3. Display original array
 *   4. Use a loop from i=0 to n/2-1:
 *      a. Swap arr[i] with arr[n-1-i] using a temp variable
 *   5. Display reversed array
 *   6. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(n) - n/2 swaps
 *   Space Complexity: O(1) - in-place, no extra array needed
 * ============================================================
 */

#include <stdio.h>

#define MAX_SIZE 100

/*
 * Function to reverse an array in-place
 * Uses the two-pointer swap technique
 * @param arr: the array to reverse
 * @param n: size of the array
 */
void reverseArray(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    int temp;

    while (left < right) {
        // ---- SWAP using temporary variable ----
        temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        // ---- MOVE POINTERS ----
        left++;
        right--;
    }
}

/*
 * Alternative: Reverse function that prints step-by-step swaps
 * Useful for understanding/debugging
 */
void reverseArrayWithSteps(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    int temp;
    int step = 1;

    printf("\n--- Reversal Steps ---\n");
    while (left < right) {
        printf("Step %d: Swap arr[%d](%d) <-> arr[%d](%d)\n",
               step, left, arr[left], right, arr[right]);

        temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        step++;
        left++;
        right--;
    }
}

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
    printf("        ARRAY REVERSAL PROGRAM\n");
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

    // ---- DISPLAY ORIGINAL ----
    printf("\n--- Original Array ---\n");
    printArray(arr, n);
    printf("\n");

    // ---- REVERSE WITH STEPS ----
    reverseArrayWithSteps(arr, n);

    // ---- DISPLAY REVERSED ----
    printf("\n--- Reversed Array ---\n");
    printArray(arr, n);
    printf("\n");

    // ---- TRICK: Reverse without extra function ----
    // You can also reverse by printing the array backwards:
    // for(i=n-1; i>=0; i--) printf("%d ", arr[i]);
    // But this doesn't MODIFY the array, only displays reversed!

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("1. Reverse a word's letters (char array)\n");
    printf("2. Undo the last N operations\n");
    printf("3. Reverse a playlist order\n");
    printf("4. Check if a word is a palindrome (compare with reversed)\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 06_array_reverse.c -o array_reverse
 *
 * SAMPLE INPUT: 5 elements -> 1 2 3 4 5
 * SAMPLE OUTPUT: { 5 4 3 2 1 }
 *
 * TRICK: To check if a string/array is a palindrome,
 *        reverse it and compare with original.
 *        If arr == reversed_arr, it's a palindrome!
 */