
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

int count_rows(char str[]) {
  int len = strlen(str);
  int counter = 1;
  for (int i = 0; i < len; i++) {
    if (str[i] == '\n') {
      counter++;
    }
  }
  return counter;
}

bool surrounded_by_four_plus(char** grid, int row, int col, int row_count,
                             int col_count) {
  int found = 0;
  for (int i = row - 1; i <= row + 1; i++) {
    if (i < 0 || i >= row_count) {
      continue;
    }
    for (int j = col - 1; j <= col + 1; j++) {
      if (j < 0 || j >= col_count) {
        continue;
      }
      if ((i != row || j != col) && grid[i][j] == '@') {
        found += 1;
      }
    }
  }
  return found >= 4;
}
int main() {
  char* file_contents = read_file("input.txt");

  char* iterator = file_contents;
  char* line;

  int row_count = count_rows(file_contents);

  char** map = malloc(sizeof(char*) * row_count);

  int col_count = 0;

  int col = 0;
  while ((line = strsep(&iterator, "\n")) != NULL) {
    col_count = strlen(line);
    map[col++] = line;
  }

  int total = 0;
  for (int i = 0; i < row_count; i++) {
    for (int j = 0; j < col_count; j++) {
      if (map[i][j] == '@') {
        if (!surrounded_by_four_plus(map, i, j, row_count, col_count)) {
          total++;
          map[i][j] = '.';
          i = -1;
          break;
        }
      }
    }
  }

  free(map);
  printf("total is: %d\n", total);
}
