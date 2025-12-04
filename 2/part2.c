#include <math.h>
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
    return NULL;
  }

  int chunk_size = 1;
  int read = fread(file_contents, chunk_size, file_size, file);

  if (read != file_size) {
    fclose(file);
    return NULL;
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
    return NULL;
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

long find_pairs(range_t* ranges, int ranges_len) {
  long total = 0;
  for (int i = 0; i < ranges_len; i++) {
    for (long j = ranges[i].start; j <= ranges[i].end; j++) {
      int num_digits = floor(log10(labs(j))) + 1;
      char* str_num = malloc(num_digits + 1);
      snprintf(str_num, num_digits + 1, "%zu", j);
      for (int k = 0; k < num_digits - 1; k++) {
        int repeated = true;
        int substring_len = k + 1;
        char* substring = malloc(sizeof(char) * substring_len + 1);

        if (substring == NULL) {
          free(ranges);
          return -1;
        }

        strncpy(substring, str_num, substring_len);
        substring[substring_len] = '\0';

        for (int l = k + 1; l < num_digits; l += substring_len) {
          char* temp = malloc(sizeof(char) * substring_len + 1);
          strncpy(temp, str_num + l, substring_len);
          temp[substring_len] = '\0';
          if (strcmp(temp, substring) != 0) {
            repeated = false;
            break;
          }
        }
        if (repeated) {
          printf("found one!%zu\n", j);
          total += j;
          break;
        }
        free(substring);
      }

      free(str_num);
    }
  }
  return total;
}

int main() {

  char* file_contents = read_file("input.txt");

  if (file_contents == NULL) {
    exit(EXIT_FAILURE);
  }

  int ranges_len;
  range_t* ranges = get_ranges(file_contents, &ranges_len);

  if (ranges == NULL) {
    free(file_contents);
    exit(EXIT_FAILURE);
  }

  long res = find_pairs(ranges, ranges_len);

  if (res < 0) {
    free(file_contents);
    free(ranges);
    free(file_contents);
    exit(EXIT_FAILURE);
  }

  printf("res is: %zu\n", res);
  free(ranges);
  free(file_contents);
}
