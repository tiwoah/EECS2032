#include <stdio.h>

int power(int base, int exponent) {
  int result = 1;

  for (int m = 0; m < exponent; m++) {
    result *= base;
  }

  return result;
}

int main() {
  int M, i, j;

  printf("Enter M, i, j: ");
  
  // Take input
  scanf("%d%d%d", &M, &i, &j);

  // Print your inputs
  printf("M: %d, i: %d, j: %d\n", M, i, j);

  int divider = power(10, i);
  int modulus = power(10, j-i+1);

  printf("%d\n", M/divider%modulus);
  
  return 0;
}
