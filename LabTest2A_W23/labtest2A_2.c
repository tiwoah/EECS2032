#include <stdio.h>

int main() {
    int N;
    printf("Input N:");
    scanf("%d", &N);

    int max = 0;
    int secondMax = 0;
    for (int i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);

        if (num > max || num > secondMax) {
            if (num > max) {
                secondMax = max;
                max = num;
            } else if (num > secondMax) {
                secondMax = num;
            }
        }
    }

    printf("Max: %d\n Second Max: %d\n", max, secondMax);
    return 0;
}