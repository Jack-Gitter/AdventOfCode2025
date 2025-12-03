#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct range {
  long start;
  long end;
} range_t;

char* read_file(char file_name[]) {
  FILE* file = fopen(file_name, "r");

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* file_contents = malloc(sizeof(char) * (file_size));

  if (file_contents == NULL) {
    fclose(file);
    exit(EXIT_FAILURE);
  }

  int chunk_size = 1;
  int read = fread(file_contents, chunk_size, file_size, file);

  if (read != file_size) {
    fclose(file);
    exit(EXIT_FAILURE);
  }

  // overwrite the \n with \0 at the end of the file
  file_contents[file_size - 1] = '\0';

  fclose(file);

  return file_contents;
}

int main() {

  char* file_contents = read_file("input.txt");

  printf("%s\n", file_contents);

  char* result = file_contents;
  char target = ',';
  int range_count = 1;

  while ((result = strchr(result, target)) != NULL) {
    range_count += 1;
    result++;
  }

  range_t* ranges = malloc(sizeof(range_t) * range_count);
  int ranges_idx = 0;

  char* iterator = file_contents;
  char* range;

  while ((range = strsep(&iterator, ",")) != NULL) {
    printf("%s\n", range);
    char* second_number = range;
    char* first_number;
    first_number = strsep(&second_number, "-");
    range_t r = {strtol(first_number, NULL, 10),
                 strtol(second_number, NULL, 10)};
    ranges[ranges_idx++] = r;
  }

  free(ranges);
  free(file_contents);
}
