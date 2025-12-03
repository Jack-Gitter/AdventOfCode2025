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

    for (int i = 0; i < num; i++) {
      if (letter == 'L') {
        if (val != 0) {
          val -= 1;
          if (val == 0) {
            res += 1;
          }
        } else {
          val = 99;
        }
      } else {
        if (val != 99) {
          val += 1;
        } else {
          val = 0;
          res += 1;
        }
      }
    }
  }

  printf("%d\n", res);
  fclose(file);
}
