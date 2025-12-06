#include <ctype.h>
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

  int column_count = 0;
  bool processing_number = false;
  bool current_char_is_num = false;

  for (int i = 0; i < strlen(file_contents) && file_contents[i] != '\n'; i++) {
    current_char_is_num = isdigit(file_contents[i]);
    if (current_char_is_num && !processing_number) {
      column_count++;
      processing_number = true;
    }
    if (!current_char_is_num) {
      processing_number = false;
    }
  }
  return column_count;
}

int main() {

  char* file_contents = read_file("input.txt");
  int row_count_before_operators = get_row_count(file_contents);
  int column_count = get_col_count(file_contents);

  long** equations = malloc(sizeof(long*) * row_count_before_operators);
  char* operators = malloc(sizeof(char) * column_count);

  char* iterator = file_contents;
  char* line;

  int curr_line = 0;
  int opp_index = 0;
  while ((line = strsep(&iterator, "\n")) != NULL && strcmp(line, "") != 0) {
    if (curr_line < column_count) {
      char* next_start = line;
      for (int i = 0; i < row_count_before_operators; i++) {
        long num = strtol(next_start, &next_start, 10);
        if (equations[curr_line] == NULL) {
          equations[row_count_before_operators] =
              malloc(sizeof(long*) * column_count);
        }
        equations[curr_line][i] = num;
      }
    } else {
      for (int i = 0; i < strlen(line); i++) {
        if (isspace(line[i])) {
          continue;
        } else {
          operators[opp_index++] = line[i];
        }
      }
    }
    curr_line++;
  }

  for (int i = 0; i < column_count; i++) {
    for (int j = 0; j < row_count_before_operators; j++) {
      printf("%lu ", equations[i][j]);
    }
    printf("\n");
  }

  long total = 0;
  for (int i = 0; i < row_count_before_operators; i++) {
    printf("operator is %c\n", operators[i]);
    long current = 0;
    if (operators[i] == '*') {
      current = 1;
    }
    for (int j = 0; j < column_count; j++) {
      printf("current number is %lu\n", equations[i][j]);
      if (operators[i] == '*') {
        current *= equations[i][j];
      } else {
        current += equations[i][j];
      }
      printf("%lu ", equations[i][j]);
    }
    total += current;
    printf("current is %lu\n", current);
    printf("\n");
  }

  free(file_contents);
  printf("total is: %lu\n", total);
}
