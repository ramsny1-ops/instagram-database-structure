/*
 * ============================================================
 * PROGRAM: Fibonacci Series
 * ============================================================
 * TOPIC: Loops, Recursion, Dynamic Programming
 * LEVEL: Beginner → Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Fibonacci numbers appear in nature everywhere:
 *   - Number of petals in a flower (lilies: 3, buttercups: 5)
 *   - Spiral patterns in sunflowers and pinecones
 *   - Branching patterns in trees
 *   - Stock market technical analysis (Fibonacci retracements)
 *   - Algorithm analysis (Fibonacci heaps, golden ratio approximations)
 *
 * WORD PROBLEM:
 * ------------
 * "A pair of rabbits reproduces every month starting from the
 *  second month. If each pair produces one new pair per month,
 *  how many pairs will there be after 12 months?
 *  (This is the original Fibonacci rabbit problem!)"
 *
 * WHAT IS THE FIBONACCI SEQUENCE?
 * ---------------------------------
 *   F(0) = 0, F(1) = 1
 *   F(n) = F(n-1) + F(n-2)  for n >= 2
 *
 *   Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
 *
 *   The ratio F(n)/F(n-1) approaches the GOLDEN RATIO ≈ 1.6180339887
 *
 * THREE APPROACHES:
 * ------------------
 *   1. Recursive (simple but SLOW - O(2^n)):
 *      Recomputes the same values repeatedly
 *   2. Iterative (efficient - O(n) time, O(1) space):
 *      Build up from base cases
 *   3. Dynamic Programming (O(n) time, O(n) space):
 *      Store all computed values in an array
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Naive recursion for fib(50) takes billions of steps!
 *      fib(30) already takes ~2.7 million recursive calls
 *   2. Always use memoization or iteration for large n
 *   3. The golden ratio φ = (1+√5)/2 ≈ 1.618 appears everywhere
 *   4. Binet's formula gives a closed-form: F(n) = (φ^n - ψ^n)/√5
 *      But floating-point errors make this unreliable for large n
 *   5. For very large Fibonacci numbers, use matrix exponentiation (O(log n))
 *   6. Pisano period: Fibonacci numbers mod m repeat periodically
 *   7. In nature, Fibonacci numbers often appear in consecutive pairs
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read the number of terms (n)
 *   3. Validate input (n >= 1)
 *   4. Method 1: Print series using iteration
 *   5. Method 2: Show nth term using iteration
 *   6. End
 *
 * COMPLEXITY:
 * ----------
 *   Iterative:
 *     Time:  O(n)
 *     Space: O(1)
 *   Recursive (naive):
 *     Time:  O(2^n) - exponential!
 *     Space: O(n) - call stack
 *   DP approach:
 *     Time:  O(n)
 *     Space: O(n) - memoization table
 * ============================================================
 */

#include <stdio.h>

/*
 * Iterative Fibonacci - returns the nth Fibonacci number
 * Most efficient approach with O(1) space
 * @param n: the position in the Fibonacci sequence (0-indexed)
 * @return: the nth Fibonacci number
 */
long long fibonacciIterative(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    long long prev2 = 0;  // F(0)
    long long prev1 = 1;  // F(1)
    long long current;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return prev1;
}

/*
 * Print the first n Fibonacci numbers
 * @param n: number of terms to print
 */
void printFibonacciSeries(int n) {
    if (n <= 0) return;

    long long a = 0, b = 1;
    printf("%lld", a);
    if (n > 1) printf(", %lld", b);

    for (int i = 2; i < n; i++) {
        long long next = a + b;
        printf(", %lld", next);
        a = b;
        b = next;
    }
}

int main() {
    int n;

    printf("============================================\n");
    printf("        FIBONACCI SERIES GENERATOR\n");
    printf("============================================\n\n");

    printf("How many terms of the Fibonacci series? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("[ERROR] Please enter a positive integer!\n");
        return 1;
    }

    if (n > 92) {
        printf("[WARNING] Beyond 92 terms, long long overflows!\n");
        printf("F(93) exceeds the range of long long.\n");
        return 1;
    }

    // ---- DISPLAY SERIES ----
    printf("\n--- First %d Terms of Fibonacci Series ---\n", n);
    printf("Series: ");
    printFibonacciSeries(n);
    printf("\n");

    // ---- DISPLAY Nth TERM ----
    long long nth = fibonacciIterative(n - 1);
    printf("\n--- The %dth Fibonacci Number ---\n", n);
    printf("F(%d) = %lld\n", n - 1, nth);

    // ---- GOLDEN RATIO APPROXIMATION ----
    if (n > 2) {
        double ratio = (double)fibonacciIterative(n - 1) / fibonacciIterative(n - 2);
        printf("\n--- Golden Ratio Connection ---\n");
        printf("F(%d)/F(%d) = %.10lf\n", n - 1, n - 2, ratio);
        printf("Golden Ratio (φ) = %.10lf\n", 1.6180339887);
        printf("Difference: %.10lf\n", ratio - 1.6180339887);
    }

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("• Nature: Petal counts, sunflower spirals\n");
    printf("• Finance: Fibonacci retracement levels in trading\n");
    printf("• Computer Science: Fibonacci heaps, algorithm analysis\n");
    printf("• Art & Architecture: Golden ratio proportions\n");
    printf("• Music: Rhythm patterns based on Fibonacci numbers\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 10_fibonacci.c -o fibonacci
 *
 * SAMPLE INPUT: 10
 * SAMPLE OUTPUT: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34
 *
 * TRICK: Never use naive recursion for Fibonacci beyond n=30!
 *        Iterative approach is 10000x faster for large n.
 *        Always check for overflow - Fibonacci grows exponentially.
 */