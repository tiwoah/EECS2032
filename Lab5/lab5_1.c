#include <stdio.h>

// Prints a single row of the right-angled triangle.
void printFilledRow(int spaces, int asterisks) {
    // Print leading spaces
    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }

    // Print the asterisks
    for (int j = 0; j < asterisks; j++) {
        printf("*");
    }

    // Newline
    printf("\n");
}

int main() {
    // leftMargin (l): number of spaces from the left edge to the first row of triangle
    // rows (m): rows of the triangle
    int leftMargin, rows;
    
    printf("Initial left margin spaces for the first row: ");
    scanf("%d", &leftMargin);
    printf("Number of rows: ");
    scanf("%d", &rows);

    printf("Triangle: \n");
    
    for (int row = 0; row < rows; row++) {
        int spaces = leftMargin - row;
        int asterisks = row + 1;

        printFilledRow(spaces, asterisks);
    }
    
    return 0;
}