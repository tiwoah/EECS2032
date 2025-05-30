#include <stdio.h>

int main() {
    int rows1, cols1;
    printf("Input rows: ");
    scanf("%d", &rows1);
    printf("Input cols: ");
    scanf("%d", &cols1);

    int arr[rows1][cols1];

    // Input elements for first matrix
    for (int row = 0; row < rows1; row++) {
        for (int col = 0; col < cols1; col++) {
            scanf("%d", *(arr + row) + col);
        }
    }

    int rows2, cols2;
    printf("Input rows: ");
    scanf("%d", &rows2);
    printf("Input cols: ");
    scanf("%d", &cols2);

    int arr2[rows2][cols2];

    // Input elements for second matrix
    for (int row = 0; row < rows2; row++) {
        for (int col = 0; col < cols2; col++) {
            scanf("%d", *(arr2 + row) + col);
        }
    }

    // Iterate every row in the first matrix
    for (int row = 0; row < rows1; row++) {
        // Check if diagonal column exists in first matrix
        if (row < cols1) {
            int diagonal1 = arr[row][row];
            // Check if row exists in second matrix
            if (row < rows2) {
                int diagonal2 = arr2[row][row];
    
                if (diagonal1 == diagonal2) {
                    // Print first matrix's row
                    for (int col = 0; col < cols1; col++) {
                        printf("%d ", arr[row][col]);
                    }
                    printf("\n");
                }
            }
        }
    }

    return 0;
}