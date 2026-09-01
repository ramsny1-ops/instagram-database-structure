/*
 * ============================================================
 * PROGRAM: Area and Perimeter of a Semi-Circle
 * ============================================================
 * TOPIC: Basic Math Operations, Variables, Input/Output
 * LEVEL: Beginner
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * An architect is designing a half-circle window (like a Gothic arch)
 * for a new building. They need to calculate:
 *   - The glass area needed (semi-circle area)
 *   - The frame length needed (semi-circle perimeter = arc + diameter)
 *
 * Another scenario: A farmer has a semi-circular plot of land bounded
 * by a straight wall and a curved fence. They need to calculate the
 * area for crop planning and the fence length.
 *
 * WORD PROBLEM:
 * ------------
 * "A semi-circular garden has a radius of 14 meters. The straight side
 *  is bordered by a wall, and the curved side needs to be fenced.
 *  Calculate: (a) the area of the garden, (b) the length of the fence
 *  needed (curved part only), and (c) the total perimeter including
 *  the diameter."
 *
 * FORMULAS:
 * ---------
 *   Area of Semi-Circle  = (π * r²) / 2
 *   Curved Arc Length    = π * r
 *   Total Perimeter      = π * r + 2 * r  = r * (π + 2)
 *
 *   Where:
 *     π (pi) ≈ 3.14159265358979323846
 *     r = radius of the semi-circle
 *
 *   IMPORTANT: Many beginners confuse "perimeter of semi-circle"
 *   with just the curved part. The FULL perimeter includes the
 *   straight diameter (2r) plus the curved arc (πr).
 *
 * TIPS & TRICKS:
 * -------------
 *   1. The semi-circle is exactly HALF of a full circle
 *   2. The perimeter of a semi-circle is NOT half the circumference
 *      of the full circle - you MUST add the diameter (2r)
 *   3. Common values to remember:
 *      - Semi-circle perimeter = r * (π + 2) ≈ r * 5.14159
 *      - For r = 7: perimeter ≈ 35.99 units
 *   4. Use M_PI from <math.h> for precision
 *   5. The curved part alone is simply π * r (half of 2πr)
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Declare variables: radius, area, curvedLength, totalPerimeter
 *   3. Prompt user for radius
 *   4. Read the radius
 *   5. Calculate area = (PI * r * r) / 2
 *   6. Calculate curvedArc = PI * r
 *   7. Calculate totalPerimeter = curvedArc + 2 * r
 *   8. Display all results
 *   9. End
 *
 * COMMON MISTAKES TO AVOID:
 * -------------------------
 *   - Forgetting to divide by 2 for the area (that's for a full circle)
 *   - Forgetting to add the diameter to the perimeter
 *   - Confusing arc length with total perimeter
 *   - Using integer division: 1/2 = 0 in C! Always use 0.5 or 1.0/2.0
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(1) - constant time operations
 *   Space Complexity: O(1) - fixed number of variables
 * ============================================================
 */

#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * Function to calculate semi-circle area
 * @param radius: the radius of the semi-circle
 * @return: area of the semi-circle
 */
double semiCircleArea(double radius) {
    return (M_PI * radius * radius) / 2.0;
}

/*
 * Function to calculate the curved arc length
 * @param radius: the radius of the semi-circle
 * @return: length of the curved arc only
 */
double curvedArcLength(double radius) {
    return M_PI * radius;
}

/*
 * Function to calculate total perimeter (arc + diameter)
 * @param radius: the radius of the semi-circle
 * @return: total perimeter of the semi-circle
 */
double semiCirclePerimeter(double radius) {
    return M_PI * radius + 2.0 * radius;
    // Factorized form: radius * (M_PI + 2.0)
}

int main() {
    double radius, area, arcLen, perimeter;

    printf("============================================\n");
    printf("    SEMI-CIRCLE AREA & PERIMETER CALCULATOR\n");
    printf("============================================\n\n");

    printf("Enter the radius of the semi-circle: ");
    scanf("%lf", &radius);

    if (radius < 0) {
        printf("\n[ERROR] Radius cannot be negative!\n");
        return 1;
    }

    // ---- CALCULATIONS ----
    area = semiCircleArea(radius);
    arcLen = curvedArcLength(radius);
    perimeter = semiCirclePerimeter(radius);

    // ---- DISPLAY RESULTS ----
    printf("\n--- Results for Radius = %.2lf ---\n\n", radius);

    printf("1. Area of Semi-Circle:     %.4lf square units\n", area);
    printf("   (Half of full circle area)\n\n");

    printf("2. Curved Arc Length:       %.4lf units\n", arcLen);
    printf("   (Half of full circle circumference)\n\n");

    printf("3. Total Perimeter:         %.4lf units\n", perimeter);
    printf("   (Curved arc + Diameter = %.4lf + %.4lf)\n", arcLen, 2.0 * radius);
    printf("   Formula: r * (π + 2) = %.2lf * %.4lf = %.4lf\n\n",
           radius, M_PI + 2.0, perimeter);

    // ---- PRACTICAL APPLICATION ----
    printf("--- Practical Applications ---\n");
    printf("Glass needed (area):        %.2lf sq units\n", area);
    printf("Fence needed (arc only):    %.2lf units\n", arcLen);
    printf("Border trim (full):         %.2lf units\n", perimeter);

    // ---- TRICK ----
    printf("\n--- Quick Trick ---\n");
    printf("For quick mental math, use π ≈ 22/7\n");
    printf("Approximate area:           %.2lf sq units\n",
           (22.0 / 7.0) * radius * radius / 2.0);
    printf("Approximate perimeter:      %.2lf units\n",
           radius * (22.0 / 7.0 + 2.0));

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 03_area_semi_circle.c -o semicircle -lm
 *
 * SAMPLE OUTPUT (radius = 14):
 *   Area:        307.8761 sq units
 *   Arc Length:  43.9823 units
 *   Perimeter:   71.9823 units
 */