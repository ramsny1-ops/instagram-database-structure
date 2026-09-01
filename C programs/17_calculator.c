/*
 * ============================================================
 * PROGRAM: Basic Calculator (with all operations)
 * ============================================================
 * TOPIC: Switch Statements, Functions, Input Validation
 * LEVEL: Beginner
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * A calculator is the first program every beginner writes.
 * But beyond the basics, calculators model:
 *   - Financial systems: Interest calculations, EMI computations
 *   - Scientific applications: Unit conversions, formula evaluations
 *   - Embedded systems: Handheld calculators, point-of-sale systems
 *   - GUI applications: Desktop calculator software
 *
 * WORD PROBLEM:
 * ------------
 * "A shopkeeper sells items at $45.50 each. A customer buys 12 items
 *  and gets a 10% discount. Write a program to calculate:
 *  (a) Total before discount, (b) Discount amount, (c) Final amount."
 *
 * OPERATIONS SUPPORTED:
 * -----------------------
 *   1. Addition (+)
 *   2. Subtraction (-)
 *   3. Multiplication (*)
 *   4. Division (/)
 *   5. Modulus (%)
 *   6. Power (^)
 *   7. Square Root (√)
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Always check for division by zero!
 *   2. Use double for division to get decimal results
 *   3. Modulus (%) only works with integers in C
 *   4. Use switch-case for clean menu-driven programs
 *   5. Handle invalid operators gracefully
 *   6. Use do-while for continuous calculation until user exits
 *   7. For power, use pow() from <math.h>
 *   8. Consider using a function pointer array for extensibility
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Display menu of operations
 *   3. Read user's choice
 *   4. Based on choice, read operands
 *   5. Perform operation using switch-case
 *   6. Display result
 *   7. Ask if user wants to continue
 *   8. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(1) per operation
 *   Space Complexity: O(1)
 * ============================================================
 */

#include <stdio.h>
#include <math.h>

char getOperator();
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double modulo(int a, int b);
double power(double base, double exp);
double squareRoot(double num);

/*
 * Display the calculator menu
 */
void displayMenu() {
    printf("\n--- Calculator Menu ---\n");
    printf("  1. Addition (+)\n");
    printf("  2. Subtraction (-)\n");
    printf("  3. Multiplication (*)\n");
    printf("  4. Division (/)\n");
    printf("  5. Modulus (%%)\n");
    printf("  6. Power (^)\n");
    printf("  7. Square Root (√)\n");
    printf("  0. Exit\n");
    printf("  Enter choice: ");
}

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
    if (b == 0) {
        printf("[ERROR] Division by zero is not allowed!\n");
        return 0;  // Return 0 as error indicator
    }
    return a / b;
}
double modulo(int a, int b) {
    if (b == 0) {
        printf("[ERROR] Modulo by zero is not allowed!\n");
        return 0;
    }
    return (double)(a % b);
}
double power(double base, double exp) { return pow(base, exp); }
double squareRoot(double num) {
    if (num < 0) {
        printf("[ERROR] Cannot calculate square root of negative number!\n");
        return -1;
    }
    return sqrt(num);
}

int main() {
    int choice;
    double num1, num2, result;
    int int1, int2;
    int running = 1;

    printf("============================================\n");
    printf("       BASIC CALCULATOR\n");
    printf("============================================\n");

    while (running) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4: {
                printf("Enter first number: ");
                scanf("%lf", &num1);
                printf("Enter second number: ");
                scanf("%lf", &num2);

                switch (choice) {
                    case 1:
                        result = add(num1, num2);
                        printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
                        break;
                    case 2:
                        result = subtract(num1, num2);
                        printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
                        break;
                    case 3:
                        result = multiply(num1, num2);
                        printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
                        break;
                    case 4:
                        result = divide(num1, num2);
                        if (num2 != 0)
                            printf("%.2lf / %.2lf = %.4lf\n", num1, num2, result);
                        break;
                }
                break;
            }
            case 5:
                printf("Enter two integers: ");
                scanf("%d %d", &int1, &int2);
                printf("%d %% %d = %.0lf\n", int1, int2, modulo(int1, int2));
                break;
            case 6:
                printf("Enter base and exponent: ");
                scanf("%lf %lf", &num1, &num2);
                result = power(num1, num2);
                printf("%.2lf ^ %.2lf = %.4lf\n", num1, num2, result);
                break;
            case 7:
                printf("Enter a number: ");
                scanf("%lf", &num1);
                result = squareRoot(num1);
                if (num1 >= 0)
                    printf("√%.2lf = %.4lf\n", num1, result);
                break;
            case 0:
                printf("\nThank you for using the Calculator! Goodbye!\n");
                running = 0;
                break;
            default:
                printf("[ERROR] Invalid choice! Please select 0-7.\n");
        }
    }

    printf("\n============================================\n");
    return 0;
}
/*
 * COMPILATION:
 *   gcc 17_calculator.c -o calculator -lm
 *
 * SAMPLE INPUT:
 *   Choice: 1, Numbers: 10 20
 * SAMPLE OUTPUT: 10.00 + 20.00 = 30.00
 *
 * TRICK: The switch-case inside switch-case pattern handles
 *        different operand types (double vs int) based on
 *        the chosen operation. This is a clean design pattern.
 */