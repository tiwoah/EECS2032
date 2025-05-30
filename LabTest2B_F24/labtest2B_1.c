// Write a C program that reads two matrices (2d array), A and B
// determines if every row sum of matrix A is strictly greater than the corresponding row sum of matrix B.


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rows, cols;

    printf("Input rows: ");
    scanf("%d", &rows);

    printf("Input cols: ");
    scanf("%d", &cols);

    // Dynamic memory allocation
    int *matrixA = malloc((rows * cols) * sizeof(int));

    if (matrixA == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Error
    }
    
    int *matrixB = malloc((rows * cols) * sizeof(int));

    if (matrixB == NULL) {
        printf("Memory allocation failed\n");
        free(matrixA);
        return 1; // Error
    }

    // Read matrix A
    printf("Input Matrix A: ");
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int *element = matrixA + (row * cols) + col;
            scanf("%d", element);
        }
    }

    // Read matrix B
    printf("Input Matrix B: ");
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int *element = matrixB + (row * cols) + col;
            scanf("%d", element);
        }
    }

    // Output our matrix just in case
    // printf("Matrix A: \n");
    // for (int row = 0; row < rows; row++) {
    //     for (int col = 0; col < cols; col++) {
    //         int *element = matrixA + (row * cols) + col;
    //         printf("%d", *element);
    //     }
    //     printf("\n");
    // }

    // printf("Matrix B: \n");
    // for (int row = 0; row < rows; row++) {
    //     for (int col = 0; col < cols; col++) {
    //         int *element = matrixB + (row * cols) + col; // Pointer Arithmetic
    //         printf("%d", *element);
    //     }
    //     printf("\n");
    // }

    // Compare matrix elements
    // Iterate row
    int failed = 0;
    for (int row = 0; row < rows; row++) {
        if (failed) break;

        // Iterate every column
        for (int col = 0; col < cols; col++) {
            int *elementA = matrixA + (row * cols) + col;
            int *elementB = matrixB + (row * cols) + col;
            
            if (*elementA <= *elementB) {
                failed = 1;
                printf("NO");
                break;
            }
        }

        // If this is the last row
        if (row == rows - 1) {
            // Previous rows must have been valid
            printf("YES");
        }
    }

    // Delete
    free(matrixA);
    free(matrixB);
    return 0;
}