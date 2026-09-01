/*
 * ============================================================
 * PROGRAM: Prime Number Checker
 * ============================================================
 * TOPIC: Loops, Mathematical Logic, Optimization
 * LEVEL: Beginner → Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Prime numbers are the backbone of modern cryptography:
 *   - RSA encryption uses two large prime numbers
 *   - Online banking and HTTPS rely on prime number properties
 *   - Hash functions use primes for better distribution
 *   - Generating random numbers often uses prime-based algorithms
 *
 * WORD PROBLEM:
 * ------------
 * "A cryptographer needs to check if 97 is a prime number before
 *  using it as an encryption key. Write a program to verify
 *  this and display all prime numbers between 1 and 100."
 *
 * WHAT IS A PRIME NUMBER?
 * --------------------------
 *   A prime number is a natural number greater than 1 that has
 *   exactly two distinct positive divisors: 1 and itself.
 *   Examples: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, ...
 *   Note: 1 is NOT prime (only one divisor).
 *
 * OPTIMIZATION STRATEGIES:
 * --------------------------
 *   1. Basic: Check all numbers from 2 to n-1 → O(n)
 *   2. Optimized: Check only up to √n → O(√n)
 *      Reason: If n = a × b, then either a ≤ √n or b ≤ √n
 *   3. Further: Skip even numbers after checking 2 → O(√n/2)
 *   4. Sieve of Eratosthenes: Find ALL primes up to N efficiently
 *
 * TIPS & TRICKS:
 * -------------
 *   1. 2 is the ONLY even prime number
 *   2. No prime number greater than 5 ends in 5
 *   3. Every prime > 3 can be written as 6k±1 (not all 6k±1 are prime!)
 *   4. Prime number theorem: ~n/ln(n) primes below n
 *   5. Trial division up to √n is sufficient and efficient enough
 *      for numbers up to ~10^12
 *   6. For very large primes, use probabilistic tests (Miller-Rabin)
 *   7. The largest known prime has over 24 million digits!
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read the number n
 *   3. If n <= 1, it's NOT prime
 *   4. If n == 2, it IS prime
 *   5. If n is even and n > 2, NOT prime
 *   6. Check odd divisors from 3 to √n
 *   7. If any divisor divides n, it's NOT prime
 *   8. Otherwise, it IS prime
 *   9. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(√n) - check up to square root
 *   Space Complexity: O(1)
 * ============================================================
 */

#include <stdio.h>
#include <math.h>

/*
 * Check if a number is prime (optimized)
 * @param n: the number to check
 * @return: 1 if prime, 0 if not prime
 */
int isPrime(int n) {
    // Handle edge cases
    if (n <= 1) return 0;   // 0 and 1 are not prime
    if (n <= 3) return 1;   // 2 and 3 are prime
    if (n % 2 == 0 || n % 3 == 0) return 0;  // Eliminate multiples of 2 and 3

    // Check divisors of the form 6k±1 up to √n
    // Why? All primes > 3 are of the form 6k±1
    int limit = (int)sqrt((double)n);
    for (int i = 5; i <= limit; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }

    return 1;
}

/*
 * Print all prime numbers from 2 to limit using trial division
 * @param limit: upper bound
 */
void printPrimes(int limit) {
    printf("Prime numbers from 2 to %d:\n", limit);
    int count = 0;
    for (int i = 2; i <= limit; i++) {
        if (isPrime(i)) {
            printf("%4d ", i);
            count++;
            if (count % 10 == 0) printf("\n");  // New line every 10
        }
    }
    printf("\nTotal primes found: %d\n", count);
}

int main() {
    int n;

    printf("============================================\n");
    printf("       PRIME NUMBER CHECKER\n");
    printf("============================================\n\n");

    printf("Enter a number to check: ");
    scanf("%d", &n);

    printf("\n--- Checking %d ---\n", n);

    if (n <= 1) {
        printf("%d is NOT a prime number.\n", n);
        printf("Tip: Prime numbers must be greater than 1.\n");
    } else if (isPrime(n)) {
        printf("%d IS a prime number! ✓\n", n);
        printf("Tip: It has exactly 2 divisors: 1 and itself.\n");

        // ---- NEAREST PRIMES ----
        // Find the prime just below n
        int below = n - 1;
        while (below > 1 && !isPrime(below)) below--;
        // Find the prime just above n
        int above = n + 1;
        while (!isPrime(above)) above++;

        printf("Nearest prime below:   %d\n", below);
        printf("Nearest prime above:   %d\n", above);
    } else {
        printf("%d is NOT a prime number. ✗\n", n);
        printf("Tip: It has divisors other than 1 and itself.\n");
    }

    // ---- SHOW ALL PRIMES UP TO n ----
    if (n >= 2 && n <= 10000) {
        printf("\n");
        printPrimes(n);
    }

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("• RSA Encryption: Product of two large primes\n");
    printf("• Hashing: Prime-sized hash tables reduce collisions\n");
    printf("• Randomness: Prime-number generators for simulations\n");
    printf("• Checksums: Prime moduli in cyclic redundancy checks\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 12_prime_number.c -o prime -lm
 *
 * SAMPLE INPUT: 97
 * SAMPLE OUTPUT: 97 IS a prime number!
 *
 * TRICK: Check divisibility up to √n only. For n=10000,
 *        instead of checking 9998 divisors, check only 100!
 *        This is a 100x speedup.
 */