#include <stdio.h>

void backwardArray(int arr[6]) {
    int temp;

    // Swap index 0 and 5
    temp = arr[0]; // COPY the value of arr[0] into temp
    arr[0] = arr[5];
    arr[5] = temp;

    // Swap index 1 and 4
    temp = arr[1]; // COPY the value of arr[1] into temp
    arr[1] = arr[4];
    arr[4] = temp;

    // Swap index 2 and 3
    temp = arr[2]; // COPY the value of arr[2] into temp
    arr[2] = arr[3];
    arr[3] = temp;
}

int main() {
    int arr[6];

    // Read 6 integers from user input
    printf("Enter 6 integers: \n");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &arr[i]);  // Read and put each integer into arr[i]
    }

    printf("Input array: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    backwardArray(arr);

    printf("Output array: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}