/*
 * ============================================================
 * PROGRAM: String Operations (Reverse, Case Convert, Count)
 * ============================================================
 * TOPIC: Strings, Pointers, Character Manipulation
 * LEVEL: Beginner → Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * String manipulation is everywhere in software:
 *   - Password validation (uppercase, lowercase, digit requirements)
 *   - Search engines: Normalizing queries (case folding)
 *   - Text editors: Find and replace, case conversion
 *   - Data cleaning: Converting CSV data formats
 *   - Chat applications: Toggling CAPS LOCK indicators
 *
 * WORD PROBLEM:
 * ------------
 * "A user registration system requires passwords to have at least
 *  one uppercase letter, one lowercase letter, and one digit.
 *  Write a program that takes a password string and checks if
 *  it meets all requirements. Also, display the password with
 *  all cases swapped and count the number of vowels."
 *
 * KEY STRING OPERATIONS:
 * ------------------------
 *   1. Reverse a string (two-pointer swap)
 *   2. Convert to uppercase (tolower/toupper)
 *   3. Convert to lowercase
 *   4. Swap case (upper↔lower)
 *   5. Count vowels, consonants, digits, spaces
 *   6. Check if string is a palindrome
 *
 * TIPS & TRICKS:
 * -------------
 *   1. In C, strings are NULL-terminated character arrays
 *   2. strrev() exists in some compilers but is NOT standard C
 *      Always implement manually for portability
 *   3. toupper() and tolower() from <ctype.h> handle locale
 *   4. ASCII values:
 *      'A'=65 to 'Z'=90, 'a'=97 to 'z'=122
 *      Difference between cases = 32
 *   5. Vowels: a, e, i, o, u (and sometimes y)
 *   6. Pointers can traverse strings efficiently: while(*str)
 *   7. String length = strlen() or manual traversal to '\0'
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read a string from user
 *   3. Reverse using two-pointer swap
 *   4. Convert cases (upper, lower, swap)
 *   5. Count character categories (vowels, consonants, digits, spaces)
 *   6. Display all results
 *   7. End
 *
 * COMPLEXITY:
 * ----------
 *   All operations: O(n) where n = string length
 *   Space Complexity: O(1) - in-place modifications
 * ============================================================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

/*
 * Reverse a string in-place using two-pointer technique
 * @param str: the string to reverse
 */
void reverseString(char str[]) {
    int left = 0;
    int right = strlen(str) - 1;
    char temp;

    while (left < right) {
        temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

/*
 * Convert entire string to uppercase
 * @param str: the string to convert
 */
void toUpperCaseString(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

/*
 * Convert entire string to lowercase
 * @param str: the string to convert
 */
void toLowerCaseString(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

/*
 * Swap case of each character
 * Uppercase → Lowercase, Lowercase → Uppercase
 * @param str: the string to modify
 */
void swapCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

/*
 * Count characters in different categories
 * @param str: the input string
 * @param vowels: output vowel count
 * @param consonants: output consonant count
 * @param digits: output digit count
 * @param spaces: output space count
 */
void countCharacters(const char str[], int *vowels, int *consonants,
                     int *digits, int *spaces) {
    *vowels = *consonants = *digits = *spaces = 0;

    for (int i = 0; str[i]; i++) {
        char ch = tolower((unsigned char)str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            (*vowels)++;
        } else if (ch >= 'a' && ch <= 'z') {
            (*consonants)++;
        } else if (ch >= '0' && ch <= '9') {
            (*digits)++;
        } else if (ch == ' ' || ch == '\t') {
            (*spaces)++;
        }
    }
}

int main() {
    char str[MAX_LEN];
    char copy[MAX_LEN];  // Preserve original

    printf("============================================\n");
    printf("       STRING OPERATIONS PROGRAM\n");
    printf("============================================\n\n");

    printf("Enter a string: ");
    scanf(" %[^\n]", str);  // Read string with spaces

    strcpy(copy, str);  // Save original copy

    int len = strlen(str);
    printf("\n--- String Info ---\n");
    printf("Original: \"%s\"\n", str);
    printf("Length:    %d characters\n", len);

    // ---- REVERSE ----
    reverseString(str);
    printf("\n--- Reversed String ---\n");
    printf("Reversed: \"%s\"\n", str);

    // ---- CASE CONVERSIONS ----
    strcpy(str, copy);  // Reset to original

    // Uppercase
    strcpy(str, copy);
    toUpperCaseString(str);
    printf("\n--- Uppercase ---\n");
    printf("Result: \"%s\"\n", str);

    // Lowercase
    strcpy(str, copy);
    toLowerCaseString(str);
    printf("\n--- Lowercase ---\n");
    printf("Result: \"%s\"\n", str);

    // Swap case
    strcpy(str, copy);
    swapCase(str);
    printf("\n--- Swap Case ---\n");
    printf("Result: \"%s\"\n", str);

    // ---- CHARACTER COUNTS ----
    strcpy(str, copy);
    int vowels, consonants, digits, spaces;
    countCharacters(str, &vowels, &consonants, &digits, &spaces);

    printf("\n--- Character Count ---\n");
    printf("Vowels:    %d\n", vowels);
    printf("Consonants:%d\n", consonants);
    printf("Digits:    %d\n", digits);
    printf("Spaces:    %d\n", spaces);
    printf("Others:    %d\n", len - vowels - consonants - digits - spaces);

    // ---- PASSWORD STRENGTH CHECK ----
    printf("\n--- Password Strength Check ---\n");
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; str[i]; i++) {
        if (isupper((unsigned char)str[i])) hasUpper = 1;
        else if (islower((unsigned char)str[i])) hasLower = 1;
        else if (isdigit((unsigned char)str[i])) hasDigit = 1;
        else if (!isspace((unsigned char)str[i])) hasSpecial = 1;
    }

    int strength = hasUpper + hasLower + hasDigit + hasSpecial;
    printf("Has uppercase: %s\n", hasUpper ? "✓" : "✗");
    printf("Has lowercase: %s\n", hasLower ? "✓" : "✗");
    printf("Has digit:     %s\n", hasDigit ? "✓" : "✗");
    printf("Has special:   %s\n", hasSpecial ? "✓" : "✗");
    printf("Strength: %d/4 → %s\n", strength,
           strength >= 4 ? "STRONG" : strength >= 2 ? "MEDIUM" : "WEAK");

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("• Password validation in registration systems\n");
    printf("• Text normalization in search engines\n");
    printf("• Case-insensitive comparison in databases\n");
    printf("• Data cleaning in ETL pipelines\n");
    printf("• Cryptography: Case and character manipulation\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 16_string_operations.c -o string_ops
 *
 * SAMPLE INPUT: "Hello World 123"
 * SAMPLE OUTPUT:
 *   Reversed: "321 dlroW olleH"
 *   Uppercase: "HELLO WORLD 123"
 *   Vowels: 3, Consonants: 7, Digits: 3, Spaces: 2
 *
 * TRICK: In C, strings are character arrays terminated by '\0'.
 *        Always ensure adequate buffer size (+1 for null terminator).
 *        Use fgets() instead of scanf() for safer input!
 */