#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct range {
  long low;
  long high;
} range_t;

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

int num_ranges(char input[]) {
  int counter = 0;
  int lines = 0;
  int i = 0;
  while (input[i] != '\0') {
    if (input[i] == '\n') {
      lines++;
      counter++;
    } else {
      counter = 0;
    }
    if (counter == 2) {
      return lines - 1;
    }
    i++;
  }
  return -1;
}
int main() {

  char* file_contents = read_file("input.txt");

  char* iterator = file_contents;
  char* line;

  int range_count = num_ranges(file_contents);
  range_t* ranges = malloc(sizeof(range_t) * range_count);
  int range_idx = 0;

  while ((line = strsep(&iterator, "\n")) != NULL && strcmp(line, "") != 0) {
    char* high_str = line;
    char* low_str = strsep(&high_str, "-");
    long low = strtol(low_str, NULL, 10);
    long high = strtol(high_str, NULL, 10);
    range_t range = {low, high};
    ranges[range_idx++] = range;
  }

  int total = 0;
  while ((line = strsep(&iterator, "\n")) != NULL && strcmp(line, "") != 0) {
    long num = strtol(line, NULL, 10);
    for (int i = 0; i < range_count; i++) {
      if (num >= ranges[i].low && num <= ranges[i].high) {
        total++;
        break;
      }
    }
  }

  printf("total is: %d\n", total);
}
