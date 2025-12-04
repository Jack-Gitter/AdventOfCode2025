#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(char file_name[]) {
  FILE* file = fopen(file_name, "r");

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* file_contents = malloc(sizeof(char) * (file_size));

  if (file_contents == NULL) {
    fclose(file);
    return NULL;
  }

  int chunk_size = 1;
  int read = fread(file_contents, chunk_size, file_size, file);

  if (read != file_size) {
    fclose(file);
    return NULL;
  }

  file_contents[file_size - 1] = '\0';

  fclose(file);

  return file_contents;
}

unsigned long get_line_joltage(char line[]) {
  stack s = init_stack();
  int line_len = strlen(line);
  printf("line is %s\n", line);
  for (int i = 0; i < line_len; i++) {
    // monotonoic stack algorithm
  }
  return to_num(&s);
}

int main() {
  char* file_contents = read_file("input.txt");

  char* iterator = file_contents;
  char* line;
  unsigned long total_joltage = 0;

  while ((line = strsep(&iterator, "\n")) != NULL) {
    unsigned long line_joltage = get_line_joltage(line);
    total_joltage += line_joltage;
  }

  printf("total is: %lu\n", total_joltage);
}
