#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct range {
  int start;
  int end;
} range;

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

  range* ranges = malloc(sizeof(range) * range_count);

  char* iterator = file_contents;
  char* range;

  while ((range = strsep(&iterator, ",")) != NULL) {
    printf("%s\n", range);
    char* second_number = range;
    char* first_number;
    first_number = strsep(&second_number, "-");
    printf("first number: %s", first_number);
    printf(" second number: %s\n", second_number);

    // parse start and end, and then create range objects and put them into
    // ranges arr
  }

  free(ranges);
  free(file_contents);
}
