/*
 * ============================================================
 * PROGRAM: Armstrong Number (Narcissistic Number) Checker
 * ============================================================
 * TOPIC: Number Operations, Loops, Power Calculation
 * LEVEL: Beginner
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Armstrong numbers (also called narcissistic or pluperfect
 * numbers) are used in recreational mathematics and number
 * theory. They help students understand place value and
 * digit manipulation in number systems. They also appear in:
 *   - Programming contests and interviews
 *   - Number theory education
 *   - Cryptographic checksums (sometimes)
 *
 * WORD PROBLEM:
 * ------------
 * "A teacher asks students: 'Is 153 an Armstrong number?'
 *  Explain why. How about 370? Find all Armstrong numbers
 *  between 100 and 999."
 *
 * WHAT IS AN ARMSTRONG NUMBER?
 * -------------------------------
 *   An n-digit number is an Armstrong number if the sum of
 *   each digit raised to the power n equals the number itself.
 *
 *   Examples:
 *     153 = 1³ + 5³ + 3³ = 1 + 125 + 27 = 153 ✓
 *     370 = 3³ + 7³ + 0³ = 27 + 343 + 0 = 370 ✓
 *     9474 = 9⁴ + 4⁴ + 7⁴ + 4⁴ = 6561 + 256 + 2401 + 256 = 9474 ✓
 *
 *   Note: For 3-digit numbers, Armstrong numbers are also
 *   called "narcissistic numbers". For n-digit, the power is n.
 *
 * KNOWN ARMSTRONG NUMBERS:
 * ---------------------------
 *   There are only 88 narcissistic numbers in base 10!
 *   The largest has 39 digits.
 *   In base 10, all single digits (0-9) are trivially Armstrong.
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Count the number of digits first (n = floor(log10(num)) + 1)
 *   2. Extract digits using % 10 and / 10
 *   3. Use pow() from <math.h> or manual multiplication for speed
 *   4. For better performance, use a lookup table for powers
 *   5. Armstrong numbers are RARE - only 88 exist in base 10
 *   6. In binary, ALL numbers are Armstrong (trivial case)
 *   7. Perfect numbers (6, 28, 496) are different from Armstrong!
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read the number
 *   3. Count the number of digits
 *   4. Extract each digit, raise to power n, accumulate sum
 *   5. Compare sum with original number
 *   6. Display result
 *   7. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(d) where d = number of digits
 *   Space Complexity: O(1)
 * ============================================================
 */

#include <stdio.h>
#include <math.h>

/*
 * Count the number of digits in a number
 * @param num: the number
 * @return: number of digits
 */
int countDigits(int num) {
    if (num == 0) return 1;
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

/*
 * Check if a number is an Armstrong number
 * @param num: the number to check
 * @return: 1 if Armstrong, 0 otherwise
 */
int isArmstrong(int num) {
    int original = num;
    int n = countDigits(num);
    int sum = 0;
    int temp = num;

    while (temp > 0) {
        int digit = temp % 10;
        sum += (int)pow((double)digit, n);
        temp /= 10;
    }

    return (sum == original);
}

/*
 * Find and display all Armstrong numbers in a range
 * @param low: lower bound
 * @param high: upper bound
 */
void findArmstrongInRange(int low, int high) {
    printf("Armstrong numbers between %d and %d:\n", low, high);
    int count = 0;
    for (int i = low; i <= high; i++) {
        if (isArmstrong(i)) {
            printf("%d  ", i);
            count++;
        }
    }
    if (count == 0) {
        printf("None found.");
    }
    printf("\nTotal: %d Armstrong number(s) found.\n", count);
}

int main() {
    int num;

    printf("============================================\n");
    printf("    ARMSTRONG NUMBER CHECKER\n");
    printf("  (Narcissistic Number Detector)\n");
    printf("============================================\n\n");

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("[ERROR] Please enter a non-negative integer.\n");
        return 1;
    }

    printf("\n--- Checking %d ---\n", num);

    int digits = countDigits(num);
    printf("Number of digits: %d\n", digits);
    printf("Power used: %d\n", digits);

    // ---- SHOW CALCULATION STEPS ----
    printf("\nCalculation:\n");
    int temp = num, sum = 0;
    printf("%d = ", num);

    // We need to reconstruct the expression
    int original = num;
    temp = num;
    int n = digits;

    // Build the expression string
    if (temp == 0) {
        printf("0^%d = 0\n", n);
    } else {
        int t = num;
        int first = 1;
        int calcSum = 0;
        while (t > 0) {
            int d = t % 10;
            calcSum += (int)pow((double)d, n);
            if (!first) printf(" + ");
            printf("%d^%d", d, n);
            first = 0;
            t /= 10;
        }
        printf(" = %d\n", calcSum);
    }

    // ---- DISPLAY RESULT ----
    if (isArmstrong(num)) {
        printf("\n★ %d IS an Armstrong Number! ✓\n", num);
        printf("Tip: Sum of digits^%d equals the number itself.\n", digits);
    } else {
        printf("\n✗ %d is NOT an Armstrong Number.\n", num);
        printf("Tip: The sum of digits raised to power %d is %d.\n", digits, sum);
    }

    // ---- FIND ALL 3-DIGIT ARMSTRONG NUMBERS ----
    printf("\n--- All 3-Digit Armstrong Numbers ---\n");
    findArmstrongInRange(100, 999);

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("• Math education: Understanding place value\n");
    printf("• Programming contests: Common interview question\n");
    printf("• Number theory: Studying digit-power relationships\n");
    printf("• Recreational math: Finding patterns in numbers\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 13_armstrong_number.c -o armstrong -lm
 *
 * SAMPLE INPUT: 153
 * SAMPLE OUTPUT: IS an Armstrong Number! (1³+5³+3³ = 153)
 *
 * TRICK: There are only 88 narcissistic numbers in base 10.
 *        The largest has 39 digits. They become increasingly
 *        rare as numbers get larger.
 */