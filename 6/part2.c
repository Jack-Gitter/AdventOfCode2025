#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(char file_name[]) {
  FILE* file = fopen(file_name, "r");

  if (file == NULL) {
    return NULL;
  }

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

int get_equation_count(char file_contents[]) {

  int counter = 0;
  bool processing_num = false;
  for (int i = 0; file_contents[i] != '\n'; i++) {
    if (isspace(file_contents[i])) {
      processing_num = false;
    } else {
      if (processing_num != true) {
        counter++;
      }
      processing_num = true;
    }
  }
  return counter;
}

int main() {

  char* file_contents = read_file("input.txt");
  int row_count = get_row_count(file_contents) + 1;
  int col_count = get_col_count(file_contents);

  char** input = malloc(sizeof(char*) * row_count - 1);

  for (int i = 0; i < row_count; i++) {
    input[i] = malloc(sizeof(char) * col_count);
  }

  int row = 0;
  int col = 0;
  int i = 0;

  while (file_contents[i] != '\0') {
    if (file_contents[i] == '\n') {
      col = 0;
      row++;
    } else {
      input[row][col++] = file_contents[i];
    }
    i++;
  }

  int equation_count = get_equation_count(file_contents);

  long** equations = malloc(sizeof(long*) * equation_count);

  for (int i = 0; i < equation_count; i++) {
    equations[i] = malloc(sizeof(long) * row_count);
  }

  int equation_row = 0;
  int equation_col = 0;
  for (int i = 0; i < col_count; i++) {
    int append_count = 0;
    char* str = malloc(sizeof(char) * row_count);
    for (int j = 0; j < row_count - 1; j++) {
      if (!isspace(input[j][i])) {
        str[append_count++] = input[j][i];
      }
    }
    str[append_count] = '\0';
    if (strlen(str) != 0) {
      long num = strtol(str, NULL, 10);
      if (equation_col == row_count - 1) {
        equation_col = 0;
        equation_row++;
      }
      equations[equation_row][equation_col++] = num;
    }
  }

  char* operators = malloc(sizeof(char) * col_count);

  int opp_idx = 0;
  for (int i = 0; i < col_count; i++) {

    char item = input[row_count - 1][i];
    if (!isspace(item)) {
      operators[opp_idx++] = item;
    }
  }

  for (int i = 0; i < col_count; i++) {
  }

  long total = 0;
  for (int i = 0; i < equation_count; i++) {
    char operator = operators[i];
    long start = 0;
    if (operator == '*') {
      start = 1;
    }
    printf("%c", operators[i]);
    for (int j = 0; j < row_count - 1; j++) {
      if (operator == '*') {
        start *= equations[i][j];
      } else {
        start += equations[i][j];
      }
      printf("%lu ", equations[i][j]);
    }
    printf(" = %lu", start);
    total += start;
    printf("\n");
  }

  printf("total is %lu\n", total);
}
