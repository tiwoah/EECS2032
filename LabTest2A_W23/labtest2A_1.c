#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;
    printf("Input rows: ");
    scanf("%d", &rows);
    printf("Input cols: ");
    scanf("%d", &cols);

    int *arr = malloc(rows * cols * sizeof(int));
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            scanf("%d", arr + (row * cols) + col);
        }
    }

    // Print array
    for (int row = 0; row < rows; row++) {
        if ((row+1) % 2 != 0) {
            continue;
        }

        for (int col = 0; col < cols; col++) {
            printf("%d   ", *(arr + (row * cols) + col));
        }

        printf("\n");
    }

    return 0;
}