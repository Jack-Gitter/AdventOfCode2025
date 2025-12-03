#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct range {
  int start;
  int end;
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

range_t* get_ranges(char file_contents[], int* ranges_len) {

  char* result = file_contents;
  char target = ',';
  int range_count = 1;

  while ((result = strchr(result, target)) != NULL) {
    range_count += 1;
    result++;
  }

  *ranges_len = range_count;

  range_t* ranges = malloc(sizeof(range_t) * range_count);

  if (ranges == NULL) {
    free(ranges);
    free(file_contents);
    exit(EXIT_FAILURE);
  }

  int ranges_idx = 0;

  char* iterator = file_contents;
  char* range;

  while ((range = strsep(&iterator, ",")) != NULL) {
    char* second_number = range;
    char* first_number;
    first_number = strsep(&second_number, "-");
    range_t r = {strtol(first_number, NULL, 10),
                 strtol(second_number, NULL, 10)};
    ranges[ranges_idx++] = r;
  }

  return ranges;
}

int main() {

  char* file_contents = read_file("input.txt");
  // these are all the ranges, now what do we do with them?
  int ranges_len;
  range_t* ranges = get_ranges(file_contents, &ranges_len);
  printf("ranges_len: %d\n", ranges_len);

  for (int i = 0; i < ranges_len; i++) {
    for (int j = ranges[i].start; j <= ranges[i].end; j++) {
      int num_digits = floor(log10(abs(j))) + 1;
      char* num_str = malloc(num_digits + 1);
      snprintf(num_str, num_digits + 1, "%d", j);
      printf("%s\n", num_str);
      if ((num_digits % 2) == 0) {
        printf("even len string found\n");
        // take the first half and the second half, compare them
      }
      free(num_str);
    }
  }

  free(ranges);
  free(file_contents);
}
