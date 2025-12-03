#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 10
int main() {
  int val = 50;
  int res = 0;

  char line[MAX_LINE_LENGTH];
  FILE* file = fopen("input.txt", "r");

  if (file == NULL) {
    exit(EXIT_FAILURE);
  }

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    char letter = line[0];

    int num = strtol(line + 1, NULL, 10);

    if (letter == 'L') {
      val = ((val - num) % 100 + 100) % 100;
    } else {
      val = ((val + num) % 100 + 100) % 100;
    }

    if (val == 0) {
      res += 1;
    }
  }
  printf("%d\n", res);
  fclose(file);
}
