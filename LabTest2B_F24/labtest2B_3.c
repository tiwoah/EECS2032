#include <stdio.h>

// Define the structure for date
struct date {
    int day;
    int month;
    int year;
};

// Function prototype
void readDate(struct date *d) {
    printf("Input day: ");
    scanf("%d", &((*d).day));

    printf("Input month: ");
    scanf("%d", &((*d).month));

    printf("Input year: ");
    scanf("%d", &((*d).year));
}

int main() {
    struct date today;

    // Call the function to read the date
    // You need to implement this function
    readDate(&today);

    // Print the date in the format dd/mm/yyyy
    // Your task is to implement the printf statement to display the date correctly
    printf("The date is: %d/%d/%d \n", today.day, today.month, today.year); // Fill in the blank to display the date in dd/mm/yyyy format

    return 0;
}