#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generates `n` random integers in the inclusive range [0, 99] and writes them to file
void generate_random_numbers(int n) {
    FILE *fp = fopen("random_numbers.txt", "w");

    if (fp == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    int newNumber;
    int max = 99;
    int min = 0;
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        newNumber = rand() % (max - min + 1) + min;
        fprintf(fp, "%d\n", newNumber);
    }

    fclose(fp);
}

// Read numbers from file and put into an array
void read_numbers(int *arr, int n) {
    FILE *fp = fopen("random_numbers.txt", "r");

    if (fp == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", arr + i);
    }

    fclose(fp);
}

// Reads from the array and calculates the mean
double calculate_mean(int *arr, int n) {
    int total = 0;

    for (int i = 0; i < n; i++) {
        total += arr[i];
    }

    return ((double) total) / n;
}

// Comparison function for sorting
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

// Sort array, calculate and return median
double calculate_median(int *arr, int n) {
    qsort(arr, n, sizeof(int), compare);

    if (n % 2 == 0) {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    } else {
        return arr[n / 2];
    }
}

// Get mode
int calculate_mode(int *arr, int n) {
    int temp[n];

    // Copy unsorted array into `temp` since we will sort it temporarily
    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }

    // Sort temporary array
    qsort(temp, n, sizeof(int), compare);

    int currentFrequency = 1; // Ensure to start with 1 since we skip the first element
    int mostFrequency = 1;
    int mode = temp[0];

    // Compare sequential elements to its previous to count frequency of that number
    for (int i = 1; i < n; i++) {
        if (temp[i - 1] == temp[i]) {
            currentFrequency++;
            
            if (currentFrequency > mostFrequency) {
                mostFrequency = currentFrequency;
                mode = temp[i];
            }
        } else {
            currentFrequency = 1; // Encountered a new number
        }
    }

    return mode;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number to generate>\n", argv[0]);
        return 1;
    }
    
    // Convert the input string argument to an integer
    int n = atoi(argv[1]);

    // Constraints
    if (n < 1 || n > 100) {
        printf("Input must be from [1, 100]");
        return 1;
    }

    int arr[n];

    generate_random_numbers(n);

    read_numbers(arr, n);

    printf("Mean: %f\n", calculate_mean(arr, n));
    printf("Median: %f\n", calculate_median(arr, n));
    printf("Mode: %d", calculate_mode(arr, n));
    
    return 0;
}