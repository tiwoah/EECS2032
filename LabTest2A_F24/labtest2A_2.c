#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("File opening failed.");
        return 1;
    }

    char line[1000];
    while (1) {
        int result = fscanf(fp, "%s", line);
        if (result == EOF) {
            if (feof(fp)) {
                printf("Reached end of file.\n");
                break;
            } else if (ferror(fp)) {
                perror("Read error occured.\n");
                break;
            }
        }

        printf("%s\n", line);
    }

    // Returns index of "XYZ"
    int pos = strcspn(line, "XYZ");
    printf("Pos: %d\n", pos);

    fclose(fp);

    return 0;
}