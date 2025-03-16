#include <stdio.h>

int main() {
    int rows, cols;

    printf("Input rows and cols:");
    scanf("%d", &rows);
    scanf("%d", &cols);

    // Constraints
    if (rows < 1 || cols > 50) {
        return 1;
    }

    // Store a (flattened) 2D matrix in a 1D array using row-major order
    int arr[rows * cols];

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            scanf("%d", (arr + (row * cols)) + col); // Pointer Arithmetic
            // scanf uses an input buffer (capable of inputting `1 2 3 4` at once)
        }
    }

    for (int row = 0; row < rows; row++) {
        int lastElement = *(arr + (row * cols)); // Set last to first index of the row using Pointer Arithmetic

        for (int col = 0; col < cols; col++) {
            int currentElement = *((arr + (row * cols)) + col);

            // We want to find rows that have non-descending order. This means sequential elements can be equal.
            if (lastElement > currentElement) {
                // Comparison is ascending. This row is invalid.
                // Break out of the loop for this row and move onto next row.
                break;
            }

            lastElement = currentElement;
            if (col == (cols - 1)) {
                // If this is the last element in the row,
                // this row must be valid (since we would've broken out of it ealier)

                // (row + 1) since the problem statement wants the row in 1-based indexing
                // %5d for right-aligned 5 spaced padding
                printf("%5d\n", row+1);
            }
        }
    }
}