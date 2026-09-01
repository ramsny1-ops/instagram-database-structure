/*
 * ============================================================
 * PROGRAM: Palindrome Checker (Number & String)
 * ============================================================
 * TOPIC: Loops, String Manipulation, Number Operations
 * LEVEL: Beginner
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Palindromes are used in:
 *   - Error detection in data transmission
 *   - DNA sequence analysis (palindromic sequences in genetics)
 *   - Security: symmetric keys in cryptography
 *   - Username validation systems
 *   - Checking if a license plate number is a palindrome
 *
 * WORD PROBLEM:
 * ------------
 * "A security system uses palindromic PIN codes. A user enters
 *  '12321'. Write a program to check if this PIN is a palindrome.
 *  If yes, grant access. If no, deny access."
 *
 * WHAT IS A PALINDROME?
 * ------------------------
 *   A sequence that reads the same forwards and backwards.
 *   Examples:
 *     Numbers:  121, 12321, 1001, 4554
 *     Strings:  "racecar", "madam", "level", "noon"
 *
 * APPROACHES:
 * ------------
 *   For Numbers:
 *     1. Reverse the number and compare with original
 *     2. Compare digits from both ends moving inward
 *   For Strings:
 *     1. Reverse the string and compare
 *     2. Two-pointer technique (left vs right)
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Negative numbers can NEVER be palindromes (-121 ≠ 121-)
 *   2. Don't convert numbers to strings just to check palindrome
 *      - do it mathematically for better performance
 *   3. For strings, ignore case and spaces for robustness
 *      "Race Car" is a palindrome ignoring case and spaces
 *   4. The two-pointer approach avoids creating a reversed copy
 *   5. Reversing only half the number saves time and avoids overflow
 *   6. Strings: use strlen() to get length, then compare arr[i] vs arr[n-1-i]
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read a number from user
 *   3. Store the original number
 *   4. Reverse the number using modulo and division
 *   5. Compare reversed with original
 *   6. Display whether it's a palindrome
 *   7. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(log n) - number of digits
 *   Space Complexity: O(1)
 * ============================================================
 */

#include <stdio.h>

/*
 * Check if a number is a palindrome
 * @param num: the number to check
 * @return: 1 if palindrome, 0 otherwise
 */
int isNumberPalindrome(int num) {
    if (num < 0) return 0;  // Negative numbers are not palindromes
    if (num < 10) return 1; // Single digit numbers are always palindromes

    int original = num;
    int reversed = 0;

    while (num > 0) {
        int digit = num % 10;         // Extract last digit
        reversed = reversed * 10 + digit;  // Append digit to reversed
        num /= 10;                    // Remove last digit
    }

    return (original == reversed);
}

/*
 * Check if a string is a palindrome using two-pointer technique
 * Case-insensitive comparison
 * @param str: the string to check
 * @return: 1 if palindrome, 0 otherwise
 */
int isStringPalindrome(const char str[]) {
    int left = 0;
    int right = 0;

    // Find string length
    while (str[right] != '\0') right++;
    right--;  // Point to last valid character

    while (left < right) {
        // Compare characters (case-insensitive)
        char leftChar = str[left];
        char rightChar = str[right];

        // Convert to lowercase for comparison
        if (leftChar >= 'A' && leftChar <= 'Z') leftChar += 32;
        if (rightChar >= 'A' && rightChar <= 'Z') rightChar += 32;

        if (leftChar != rightChar) return 0;

        left++;
        right--;
    }

    return 1;
}

int main() {
    int choice;

    printf("============================================\n");
    printf("       PALINDROME CHECKER\n");
    printf("============================================\n\n");

    printf("Choose what to check:\n");
    printf("  1. Number\n");
    printf("  2. String\n");
    printf("  Enter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // ---- NUMBER PALINDROME ----
        int num;
        printf("\n--- Number Palindrome Check ---\n");
        printf("Enter a number: ");
        scanf("%d", &num);

        printf("\nOriginal number: %d\n", num);

        if (isNumberPalindrome(num)) {
            printf("Result: [%d] IS a palindrome! ✓\n", num);
            printf("Tip: Reads the same forwards and backwards.\n");

            // ---- SHOW REVERSE ----
            int temp = num, reversed = 0;
            while (temp > 0) {
                reversed = reversed * 10 + temp % 10;
                temp /= 10;
            }
            printf("Reversed: %d (same as original)\n", reversed);
        } else {
            printf("Result: [%d] is NOT a palindrome. ✗\n", num);
        }

    } else if (choice == 2) {
        // ---- STRING PALINDROME ----
        char str[100];
        printf("\n--- String Palindrome Check ---\n");
        printf("Enter a string: ");
        scanf(" %[^\n]", str);  // Read string with spaces

        printf("\nOriginal string: \"%s\"\n", str);

        if (isStringPalindrome(str)) {
            printf("Result: \"%s\" IS a palindrome! ✓\n", str);
        } else {
            printf("Result: \"%s\" is NOT a palindrome. ✗\n", str);
        }

        // ---- ADDITIONAL: Show reversed ----
        int len = 0;
        while (str[len] != '\0') len++;
        printf("Reversed: \"");
        for (int i = len - 1; i >= 0; i--) {
            printf("%c", str[i]);
        }
        printf("\"\n");

    } else {
        printf("[ERROR] Invalid choice!\n");
        return 1;
    }

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("• Security: Palindromic PIN codes\n");
    printf("• Genetics: DNA palindromic sequences\n");
    printf("• Data validation: Error detection in transmission\n");
    printf("• Fun: Palindromic phrases: 'A man, a plan, a canal: Panama'\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 11_palindrome.c -o palindrome
 *
 * SAMPLE INPUT: 12321
 * SAMPLE OUTPUT: IS a palindrome!
 *
 * TRICK: For numbers, you can also reverse only HALF the number
 *        to avoid integer overflow issues with very large palindromes.
 *        If reversed_half == remaining_half, it's a palindrome.
 */