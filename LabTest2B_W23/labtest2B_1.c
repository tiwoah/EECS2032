#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
  printf("Input string: ");
  char string[50];
  scanf("%s", string);

  int noC = 0;
  for (int i = 0; i < strlen(string); i++) {
    if (islower(string[i])) {
      noC++;
    }
  }

  printf("Number of lowercase characters: %d\n", noC);
  return 0;
}
