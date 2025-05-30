#include <stdio.h>
#include <string.h>

int main() {
    char string[50];

    scanf("%s", string);

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] != string[strlen(string)-1-i]) {
            printf("NO\n");
            break;
        }
        if (i == strlen(string) - 1) {
            printf("YES\n");
        }
    }

    return 0;
}