// Write a C program to process a student records file and display information based on a search for a student’s last name.

#include <stdio.h>
#include <string.h>

int main() {
    char lastNameToSearch[10];
    scanf("%s", lastNameToSearch);

    // Process the file
    FILE *fp = fopen("stuRec.txt", "r");

    if (fp == NULL) {
        printf("File opening failed!");
        return 1;
    }
    
    int occurances = 0;
    while(1) {
        char first[10];
        char last[10];
        int score1;
        int score2;
        int score3;

        int result = fscanf(fp, "%s %s %d %d %d", first, last, &score1, &score2, &score3);

        if (result == EOF) {
            printf("THE END\n");
            break;
        } else {
            // printf("%s\n", first);

            if (strstr(last, lastNameToSearch) != NULL) {
                // Found an occurance
                occurances++;

                printf("%-10s %-10s %d %d %d\n", first, last, score1, score2, score3);
            }
        }
    }

    if (occurances == 0) {
        printf("No occurances found.");
    }

    fclose(fp);
    return 0;
}