/*
 * ============================================================
 * PROGRAM: Factorial of a Number (Iterative & Recursive)
 * ============================================================
 * TOPIC: Functions, Loops, Recursion
 * LEVEL: Beginner → Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Factorials are used in combinatorics, probability, and
 * statistics. For example:
 *   - How many ways can 5 books be arranged on a shelf?
 *     Answer: 5! = 120 permutations
 *   - In a round-robin tournament with 8 teams, the number
 *     of matches = 8! / (2! * 6!) = 28
 *   - Probability calculations, lottery odds, etc.
 *
 * WORD PROBLEM:
 * ------------
 * "A quiz show has 5 contestants. The host wants to select
 *  a winner and a runner-up. In how many different ways
 *  can this be done? (Hint: Think about permutations = 5! / 3!)"
 *
 * WHAT IS FACTORIAL?
 * --------------------
 *   n! = n × (n-1) × (n-2) × ... × 2 × 1
 *   0! = 1 (by definition)
 *   5! = 5 × 4 × 3 × 2 × 1 = 120
 *
 * TWO APPROACHES:
 * ---------------
 *   1. Iterative: Use a loop to multiply from 1 to n
 *   2. Recursive: n! = n × (n-1)!  with base case 0! = 1
 *      This is the classic example of recursion.
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Factorial grows VERY fast: 13! overflows even long long
 *   2. 0! = 1 is a mathematical convention (empty product)
 *   3. For large n, use logarithms or big integer libraries
 *   4. Recursion uses the call stack - deep recursion can overflow
 *   5. Iterative approach is more memory-efficient
 *   6. Factorial has overlapping subproblems → can use memoization
 *   7. Use unsigned long long for larger values (up to 20!)
 *   8. Tail recursion optimization: some compilers optimize
 *      recursive factorial to loop-like performance
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read the number n
 *   3. If n < 0, error (factorial not defined for negatives)
 *   4. If n == 0, return 1
 *   5. Else, compute factorial iteratively or recursively
 *   6. Display the result
 *   7. End
 *
 * COMPLEXITY:
 * ----------
 *   Iterative:
 *     Time:  O(n)
 *     Space: O(1)
 *   Recursive:
 *     Time:  O(n)
 *     Space: O(n) - call stack depth
 * ============================================================
 */

#include <stdio.h>

/*
 * Iterative Factorial
 * Uses a simple loop
 * @param n: the number to compute factorial for
 * @return: n! as unsigned long long
 */
unsigned long long factorialIterative(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

/*
 * Recursive Factorial
 * n! = n * (n-1)!
 * Base case: 0! = 1
 * @param n: the number to compute factorial for
 * @return: n! as unsigned long long
 */
unsigned long long factorialRecursive(int n) {
    if (n == 0 || n == 1) return 1;  // Base case
    return n * factorialRecursive(n - 1);  // Recursive case
}

int main() {
    int n;

    printf("============================================\n");
    printf("      FACTORIAL CALCULATOR\n");
    printf("  (Iterative + Recursive Comparison)\n");
    printf("============================================\n\n");

    printf("Enter a non-negative integer: ");
    scanf("%d", &n);

    // ---- VALIDATION ----
    if (n < 0) {
        printf("\n[ERROR] Factorial is not defined for negative numbers!\n");
        printf("Tip: Factorial is only defined for n >= 0.\n");
        return 1;
    }

    if (n > 20) {
        printf("\n[WARNING] Factorial of %d is too large!\n", n);
        printf("20! = 2,432,902,008,176,640,000 (max for unsigned long long)\n");
        printf("Numbers above 20 will cause overflow.\n");
        return 1;
    }

    // ---- ITERATIVE CALCULATION ----
    unsigned long long iterResult = factorialIterative(n);

    // ---- RECURSIVE CALCULATION ----
    unsigned long long recResult = factorialRecursive(n);

    // ---- DISPLAY RESULTS ----
    printf("\n--- Factorial of %d ---\n\n", n);
    printf("Iterative Result: %llu\n", iterResult);
    printf("Recursive Result: %llu\n", recResult);

    // ---- VERIFICATION ----
    if (iterResult == recResult) {
        printf("\n[OK] Both methods produce the same result. ✓\n");
    } else {
        printf("\n[WARNING] Results differ! Check for overflow.\n");
    }

    // ---- SHOW CALCULATION STEPS ----
    printf("\n--- Calculation Steps ---\n");
    printf("%d! = ", n);
    for (int i = n; i > 1; i--) {
        printf("%d × ", i);
    }
    printf("1 = %llu\n", iterResult);

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("Permutations: %d people can line up in %llu ways\n", n, iterResult);
    printf("Combinations: C(%d,2) = %llu ways to choose 2 from %d\n",
           n, iterResult / 2, n);

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 09_factorial.c -o factorial
 *
 * SAMPLE INPUT: 5
 * SAMPLE OUTPUT: 120
 *
 * TRICK: Recursion is elegant but uses O(n) stack space.
 *        Always prefer iteration for production code.
 *        Recursion shines in tree/graph problems where iteration is complex.
 */