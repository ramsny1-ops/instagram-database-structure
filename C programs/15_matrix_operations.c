/*
 * ============================================================
 * PROGRAM: Matrix Addition and Multiplication
 * ============================================================
 * TOPIC: 2D Arrays, Matrix Operations
 * LEVEL: Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Matrices are fundamental in:
 *   - Computer graphics: 3D transformations (rotation, scaling, translation)
 *   - Machine learning: Weight matrices in neural networks
 *   - Physics: Transformation matrices, quantum mechanics
 *   - Image processing: Pixel arrays as matrices
 *   - Economics: Input-output models (Leontief matrices)
 *
 * WORD PROBLEM:
 * ------------
 * "A company has 3 factories (rows) producing 4 products (columns).
 *  The production matrix A shows units per day. Another matrix B
 *  shows the production increase for each factory-product pair.
 *  Calculate the new production matrix A + B.
 *  Also, if there's a 4×3 distribution matrix C, compute A×C
 *  to find the final distribution across warehouses."
 *
 * MATRIX OPERATIONS:
 * --------------------
 *   Addition: C[i][j] = A[i][j] + B[i][j]
 *     - Both matrices must have same dimensions (m×n)
 *
 *   Multiplication: C[i][j] = Σ(A[i][k] * B[k][j]) for k=0 to n-1
 *     - Matrix A must be m×n, Matrix B must be n×p
 *     - Result C is m×p
 *     - IMPORTANT: Matrix multiplication is NOT commutative!
 *       A×B ≠ B×A in general
 *
 * TIPS & TRICKS:
 * -------------
 *   1. For multiplication, the number of COLUMNS of A must equal
 *      the number of ROWS of B
 *   2. Matrix multiplication has O(n³) time complexity for n×n matrices
 *   3. Strassen's algorithm can do it in O(n^2.81)
 *   4. Use typedef for cleaner matrix declarations
 *   5. Initialize matrices to 0 before accumulation in multiplication
 *   6. Think of A[i][k] as "row i of A, column k"
 *   7. The triple nested loop is the core: i (row of A), j (col of B), k (dot product)
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Read dimensions and elements of Matrix A
 *   3. Read dimensions and elements of Matrix B
 *   4. For addition: check same dimensions, add element-wise
 *   5. For multiplication: check compatibility, compute dot products
 *   6. Display both results
 *   7. End
 *
 * COMPLEXITY:
 * ----------
 *   Addition:     O(m×n)
 *   Multiplication: O(m×n×p) for m×n and n×p matrices
 *   Space Complexity: O(m×n) for result matrices
 * ============================================================
 */

#include <stdio.h>

#define MAX 10

/*
 * Add two matrices
 * @param a: first matrix
 * @param b: second matrix
 * @param result: output matrix
 * @param rows: number of rows
 * @param cols: number of columns
 */
void addMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX],
                 int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

/*
 * Multiply two matrices
 * A is rowsA × colsA, B is colsA × colsB
 * Result is rowsA × colsB
 * @param a: first matrix
 * @param b: second matrix
 * @param result: output matrix
 * @param rowsA: rows of A
 * @param colsA: cols of A (= rows of B)
 * @param colsB: cols of B
 */
void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX],
                      int rowsA, int colsA, int colsB) {
    // Initialize result to 0
    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < colsB; j++)
            result[i][j] = 0;

    // Triple nested loop for matrix multiplication
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

/*
 * Print a matrix
 */
void printMatrix(int mat[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("| ");
        for (int j = 0; j < cols; j++) {
            printf("%4d ", mat[i][j]);
        }
        printf("|\n");
    }
}

int main() {
    int a[MAX][MAX], b[MAX][MAX], sum[MAX][MAX], product[MAX][MAX];
    int rowsA, colsA, rowsB, colsB;

    printf("============================================\n");
    printf("     MATRIX ADDITION & MULTIPLICATION\n");
    printf("============================================\n\n");

    // ---- INPUT MATRIX A ----
    printf("--- Matrix A ---\n");
    printf("Enter rows and columns: ");
    scanf("%d %d", &rowsA, &colsA);

    printf("Enter %d elements (%d×%d):\n", rowsA * colsA, rowsA, colsA);
    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < colsA; j++) {
            printf("  A[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }

    // ---- INPUT MATRIX B ----
    printf("\n--- Matrix B ---\n");
    printf("Enter rows and columns: ");
    scanf("%d %d", &rowsB, &colsB);

    printf("Enter %d elements (%d×%d):\n", rowsB * colsB, rowsB, colsB);
    for (int i = 0; i < rowsB; i++)
        for (int j = 0; j < colsB; j++) {
            printf("  B[%d][%d]: ", i, j);
            scanf("%d", &b[i][j]);
        }

    // ---- MATRIX ADDITION ----
    if (rowsA == rowsB && colsA == colsB) {
        addMatrices(a, b, sum, rowsA, colsA);
        printf("\n--- Matrix Addition (A + B) ---\n");
        printMatrix(sum, rowsA, colsA);
    } else {
        printf("\n[WARNING] Matrices must have the same dimensions for addition.\n");
        printf("A is %d×%d, B is %d×%d. Cannot add.\n",
               rowsA, colsA, rowsB, colsB);
    }

    // ---- MATRIX MULTIPLICATION ----
    if (colsA == rowsB) {
        multiplyMatrices(a, b, product, rowsA, colsA, colsB);
        printf("\n--- Matrix Multiplication (A × B) ---\n");
        printf("Result dimensions: %d × %d\n", rowsA, colsB);
        printMatrix(product, rowsA, colsB);

        // ---- VERIFY NON-COMMUTATIVE ----
        if (rowsB == colsA && colsB == rowsA) {
            int product2[MAX][MAX];
            multiplyMatrices(b, a, product2, rowsB, colsB, colsA);
            printf("\n--- B × A (to show non-commutativity) ---\n");
            printMatrix(product2, rowsB, colsB);

            // Check if equal
            int equal = 1;
            for (int i = 0; i < rowsA && equal; i++)
                for (int j = 0; j < colsA && equal; j++)
                    if (product[i][j] != product2[i][j]) equal = 0;

            if (!equal) {
                printf("\n[NOTE] A×B ≠ B×A → Matrix multiplication is NOT commutative!\n");
            }
        }
    } else {
        printf("\n[WARNING] Cannot multiply: Columns of A (%d) ≠ Rows of B (%d)\n",
               colsA, rowsB);
    }

    // ---- PRACTICAL APPLICATION ----
    printf("\n--- Practical Applications ---\n");
    printf("• Graphics: Transform vertices by transformation matrices\n");
    printf("• ML: Forward pass in neural networks (weight × input)\n");
    printf("• Physics: Rotate objects in 2D/3D space\n");
    printf("• Economics: Input-output analysis (Leontief model)\n");
    printf("• Statistics: Covariance matrices, correlation matrices\n");

    printf("\n============================================\n");

    return 0;
}
/*
 * COMPILATION:
 *   gcc 15_matrix_operations.c -o matrix_ops
 *
 * SAMPLE INPUT:
 *   A: 2×2 -> 1 2 / 3 4
 *   B: 2×2 -> 5 6 / 7 8
 * SAMPLE OUTPUT:
 *   Sum: 6 8 / 10 12
 *   Product: 19 22 / 43 50
 *
 * TRICK: Matrix multiplication's inner loop (k) computes the dot
 *        product of row i of A with column j of B.
 *        Visualize it as: result[i][j] = dot(A_row_i, B_col_j)
 */