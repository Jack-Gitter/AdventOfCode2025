#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // read from the file
  FILE* file = fopen("input.txt", "r");

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* file_contents = malloc(sizeof(char) * (file_size + 1));

  if (file_contents == NULL) {
    fclose(file);
    exit(EXIT_FAILURE);
  }

  fread(file_contents, file_size, 1, file);
  file_contents[file_size] = '\0';

  printf("%s\n", file_contents);

  char* iterator = file_contents;
  char* range;

  while ((range = strsep(&iterator, ",")) != NULL) {
    printf("%s\n", range);
  }

  free(file_contents);
  fclose(file);
}
