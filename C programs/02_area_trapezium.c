/*
 * ============================================================
 * PROGRAM: Area of a Trapezium (Trapezoid)
 * ============================================================
 * TOPIC: Basic Math Operations, Variables, Input/Output
 * LEVEL: Beginner
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * A civil engineer needs to calculate the cross-sectional area of a
 * trapezoidal canal to determine how much water it can hold.
 * The canal has two parallel sides (top width and bottom width) and
 * a depth (height). This calculation is critical for irrigation
 * planning and flood management.
 *
 * WORD PROBLEM:
 * ------------
 * "A farmer has a trapezoidal field. The parallel sides measure 10m
 *  and 6m, and the distance between them (height) is 8m. The farmer
 *  wants to plough the entire field. Calculate the area to determine
 *  how much seed is needed (if 1kg seed covers 50 sq.m)."
 *
 * FORMULAS:
 * ---------
 *   Area of Trapezium = 0.5 * (a + b) * h
 *
 *   Where:
 *     a = length of first parallel side (base1)
 *     b = length of second parallel side (base2)
 *     h = height (perpendicular distance between parallel sides)
 *
 *   Derivation: A trapezium can be thought of as a rectangle with
 *   two triangles on the sides. The formula averages the two bases
 *   and multiplies by the height.
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Note the American spelling "trapezoid" vs British "trapezium"
 *   2. The formula works for ALL trapeziums regardless of the
 *      non-parallel side lengths
 *   3. We can also calculate using the median: Area = median * height
 *      where median = (a + b) / 2
 *   4. Always validate inputs - sides and height must be positive
 *   5. For integer inputs, the result may still be a float - use double
 *   6. Practical tip: If a == b, the trapezium becomes a rectangle,
 *      and formula simplifies to a * h (our code handles this!)
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Declare variables: base1, base2, height, area
 *   3. Prompt user for all three values
 *   4. Read the inputs
 *   5. Validate all inputs are positive
 *   6. Calculate area = 0.5 * (base1 + base2) * height
 *   7. Display the result
 *   8. End
 *
 * EXTENSION IDEAS:
 * ---------------
 *   - Calculate the perimeter if all four sides are known
 *   - Determine if it's an isosceles trapezium (non-parallel sides equal)
 *   - Calculate the centroid of the trapezium
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(1) - constant time operations
 *   Space Complexity: O(1) - fixed number of variables
 * ============================================================
 */

#include <stdio.h>

/*
 * Function to compute area of a trapezium
 * @param base1: length of the first parallel side
 * @param base2: length of the second parallel side
 * @param height: perpendicular distance between the parallel sides
 * @return: area of the trapezium
 */
double trapeziumArea(double base1, double base2, double height) {
    return 0.5 * (base1 + base2) * height;
}

int main() {
    double base1, base2, height, area;
    char continueCalc;

    printf("============================================\n");
    printf("      AREA OF TRAPEZIUM CALCULATOR\n");
    printf("============================================\n\n");

    // ---- USER INPUT ----
    printf("Enter the length of the first parallel side (base1): ");
    scanf("%lf", &base1);

    printf("Enter the length of the second parallel side (base2): ");
    scanf("%lf", &base2);

    printf("Enter the height (perpendicular distance): ");
    scanf("%lf", &height);

    // ---- VALIDATION ----
    if (base1 <= 0 || base2 <= 0 || height <= 0) {
        printf("\n[ERROR] All dimensions must be positive values!\n");
        printf("Tip: A trapezium cannot have zero or negative sides.\n");
        return 1;
    }

    // ---- CALCULATION ----
    area = trapeziumArea(base1, base2, height);

    // ---- DISPLAY RESULTS ----
    printf("\n--- Input Summary ---\n");
    printf("Base 1 (parallel side):  %.2lf units\n", base1);
    printf("Base 2 (parallel side):  %.2lf units\n", base2);
    printf("Height:                  %.2lf units\n", height);

    printf("\n--- Result ---\n");
    printf("Area of Trapezium:       %.4lf square units\n", area);

    // ---- SPECIAL CASE DETECTION ----
    if (base1 == base2) {
        printf("\n[NOTE] Both parallel sides are equal! This is actually a rectangle.\n");
        printf("Rectangle Area = base * height = %.2lf * %.2lf = %.2lf\n",
               base1, height, base1 * height);
    }

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Application ---\n");
    printf("If 1 kg of seed covers 50 sq.m:\n");
    printf("Seed required:           %.2f kg\n", area / 50.0);

    printf("\n--- Alternative Formulas ---\n");
    printf("Using median method:     Median = (%.2lf + %.2lf)/2 = %.2lf\n",
           base1, base2, (base1 + base2) / 2.0);
    printf("Area = median * height = %.2lf * %.2lf = %.2lf\n",
           (base1 + base2) / 2.0, height,
           ((base1 + base2) / 2.0) * height);

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 02_area_trapezium.c -o trapezium
 *
 * SAMPLE OUTPUT (bases=10,6; height=8):
 *   Area: 64.0000 square units
 */