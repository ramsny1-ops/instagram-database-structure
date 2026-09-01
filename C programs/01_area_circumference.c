/*
 * ============================================================
 * PROGRAM: Area and Circumference of a Circle
 * ============================================================
 * TOPIC: Basic Math Operations, Variables, Input/Output
 * LEVEL: Beginner
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Imagine you are a landscape architect designing a circular garden.
 * You need to calculate:
 *   - How much fencing you need (Circumference)
 *   - How much grass/soil you need to cover the ground (Area)
 *
 * WORD PROBLEM:
 * ------------
 * "A circular park has a radius of 7 meters. The city council wants to
 *  install a fence around the park and lay turf on the ground.
 *  Calculate the length of the fence needed and the area of turf required."
 *
 * FORMULAS:
 * ---------
 *   Area        = π * r²
 *   Circumference = 2 * π * r
 *
 *   Where:
 *     π (pi) ≈ 3.14159265358979323846
 *     r = radius of the circle
 *
 * TIPS & TRICKS:
 * -------------
 *   1. We use M_PI from <math.h> for maximum precision of π
 *   2. If <math.h> M_PI is not defined, we define _USE_MATH_DEFINES
 *      or manually define PI as a macro/constant
 *   3. Always use double (not float) for higher precision in geometric calcs
 *   4. When compiling, link the math library with -lm flag:
 *      gcc program.c -o program -lm
 *   5. The %lf format specifier is used with scanf for double variables
 *   6. We wrap the calculation in a function for reusability
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Declare variables: radius, area, circumference
 *   3. Prompt user for radius input
 *   4. Read the radius value
 *   5. Calculate area = PI * radius * radius
 *   6. Calculate circumference = 2 * PI * radius
 *   7. Display both results with appropriate formatting
 *   8. End
 *
 * COMMON MISTAKES TO AVOID:
 * -------------------------
 *   - Forgetting to use double and using int (loses decimal precision)
 *   - Writing radius*radius instead of radius*radius (same but clearer as pow())
 *   - Not linking math library when using <math.h> functions
 *   - Using %f instead of %lf in scanf for double variables
 *   - Mixing up area and circumference formulas
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(1) - constant time operations
 *   Space Complexity: O(1) - fixed number of variables
 * ============================================================
 */

#include <stdio.h>
#include <math.h>    // For M_PI and mathematical functions

// Define PI constant if M_PI is not available
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * Function to calculate the area of a circle
 * @param radius: the radius of the circle
 * @return: the computed area
 */
double calculateArea(double radius) {
    return M_PI * radius * radius;
}

/*
 * Function to calculate the circumference of a circle
 * @param radius: the radius of the circle
 * @return: the computed circumference
 */
double calculateCircumference(double radius) {
    return 2.0 * M_PI * radius;
}

int main() {
    double radius, area, circumference;

    // ---- PROGRAM HEADER ----
    printf("============================================\n");
    printf("   AREA & CIRCUMFERENCE OF A CIRCLE CALCULATOR\n");
    printf("============================================\n\n");

    // ---- USER INPUT ----
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);  // %lf for double variables

    // ---- VALIDATION ----
    if (radius < 0) {
        printf("\n[ERROR] Radius cannot be negative! Please enter a positive value.\n");
        return 1;  // Exit with error code
    }

    // ---- CALCULATIONS ----
    area = calculateArea(radius);
    circumference = calculateCircumference(radius);

    // ---- OUTPUT RESULTS ----
    printf("\n--- Results ---\n");
    printf("Radius:                %.4lf units\n", radius);
    printf("Area:                  %.4lf square units\n", area);
    printf("Circumference:         %.4lf units\n", circumference);

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("Fencing needed:        %.2lf units\n", circumference);
    printf("Ground coverage:       %.2lf sq units\n", area);

    printf("\n============================================\n");
    printf("   CALCULATION COMPLETE\n");
    printf("============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 01_area_circumference.c -o area_circ -lm
 *
 * SAMPLE OUTPUT (radius = 7):
 *   Area:        153.9380 square units
 *   Circumference: 43.9823 units
 */