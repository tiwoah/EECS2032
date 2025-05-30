#include <stdio.h>

int main() {
    int N;
    printf("Input N:");
    scanf("%d", &N);

    int vector[N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &vector[i]);
    }

    int maxDifference = 0;
    int n1;
    int n2;
    for (int i = 0; i < N - 1; i++) {
        int difference = vector[i] - vector[i+1];

        if (difference < 0) {
            difference *= -1;
        }

        if (difference > maxDifference) {
            maxDifference = difference;
            n1 = vector[i];
            n2 = vector[i+1];
        }
        printf("The difference (absolute) between a[%d] and a[%d] is %d\n", i, i+1, difference);
    }

    printf("%d %d %d", n1, n2, maxDifference);

    return 0;
}