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

int get_row_count(char file_contents[]) {

  int lines_before_operators = 0;
  for (int i = 0; i < strlen(file_contents); i++) {
    if (file_contents[i] == '\n') {
      lines_before_operators++;
    }
  }
  return lines_before_operators;
}

int get_col_count(char file_contents[]) {

  int i = 0;
  while (file_contents[i] != '\n') {
    i++;
  }
  return i;
}

int main() {

  char* file_contents = read_file("input.txt");
  int row_count = get_row_count(file_contents) + 1;
  int column_count = get_col_count(file_contents);
  printf("row count %d col count %d\n", row_count, column_count);

  char** input = malloc(sizeof(char*) * row_count);
  long** equations = malloc(sizeof(long*) * (row_count - 1));

  int row = 0;
  int col = 0;
  for (int i = 0; file_contents[i] != '\0'; i++) {
    col++;
    if (file_contents[i] == '\n') {
      col = 0;
      row++;
      continue;
    }
    if (input[row] == NULL) {
      input[row] = malloc(sizeof(char) * column_count);
    }
    input[row][col] = file_contents[i];
  }

  // parse the input by looping just the other way, go column
  // by column to get the numbers

  for (int i = 0; i <= column_count; i++) {
    char num[row_count];
    for (int j = 0; j < row_count - 1; j++) {
      num[j] = input[j][i];
      if (equations[i] == NULL) {
        equations[i] = malloc(sizeof(long) * row_count);
      }
      long number = strtol(num, NULL, 10);
      equations[i][j] = number;
      // printf("%c", input[j][i]);
    }
    printf("\n");
  }
}
