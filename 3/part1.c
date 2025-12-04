#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct joltage {
  char first_num;
  int first_num_idx;
  char second_num;
  int second_num_idx;
} joltage_t;

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

joltage_t get_line_joltage(char line[]) {
  joltage_t line_joltage = {};
  for (int i = 0; i < strlen(line) - 1; i++) {
    if (i == 0) {
      line_joltage.first_num = line[i];
      line_joltage.first_num_idx = i;
    } else {
      int new_num = line[i] - '0';
      int current_num = line_joltage.first_num - '0';
      if (new_num > current_num) {
        line_joltage.first_num = line[i];
        line_joltage.first_num_idx = i;
      }
    }
  }
  for (int i = line_joltage.first_num_idx + 1; i < strlen(line); i++) {
    if (i == line_joltage.first_num_idx + 1) {
      line_joltage.second_num = line[i];
      line_joltage.second_num_idx = i;
    } else {
      int new_num = line[i] - '0';
      int current_num = line_joltage.second_num - '0';
      if (new_num > current_num) {
        line_joltage.second_num = line[i];
        line_joltage.second_num_idx = i;
      }
    }
  }
  return line_joltage;
}
int main() {
  char* file_contents = read_file("input.txt");

  char* iterator = file_contents;
  char* line;
  long total_joltage = 0;

  while ((line = strsep(&iterator, "\n")) != NULL) {
    joltage_t line_joltage = get_line_joltage(line);
    char joltage[3];
    joltage[0] = line_joltage.first_num;
    joltage[1] = line_joltage.second_num;
    joltage[2] = '\0';
    int max_joltage = strtol(joltage, NULL, 10);
    total_joltage += max_joltage;
  }

  printf("total is: %zu\n", total_joltage);
}
