#include <stdio.h>

void applyPotion(int *age, int *strength, float *weight, int *wisdom) {
    if (*age <= 25) {
        *strength *= 2;
    } else if (*age <= 40) {
        *weight *= 0.9;
    } else {
        *wisdom += 5;
    }
}

int main() {
    int age, strength, wisdom;
    float weight;

    printf("Enter age: ");
    scanf("%d", &age);

    printf("Enter strength level: ");
    scanf("%d", &strength);

    printf("Enter weight: ");
    scanf("%f", &weight);

    printf("Enter wisdom level: ");
    scanf("%d", &wisdom);

    int *agePtr = &age;
    int *strengthPtr = &strength;
    float *weightPtr = &weight;
    int *wisdomPtr = &wisdom;
    applyPotion(agePtr, strengthPtr, weightPtr, wisdomPtr);

    printf("After drinking the Reversal Potion: \n");
    printf("Age: %d\n", age);
    printf("Strength Level: %d\n", strength);
    printf("Weight: %.1f\n", weight);
    printf("Wisdom Level: %d\n", wisdom);
    
    return 0;
}