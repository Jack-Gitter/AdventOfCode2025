#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct range {
  unsigned long low;
  unsigned long high;
} range_t;

void merge_sort(range_t arr[], int left, int right) {

  if (left >= right) {
    return;
  }
  int mid = (left + right) / 2;
  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int left_len = mid - left + 1;
  int right_len = right - mid;

  range_t* left_arr = malloc(sizeof(range_t) * left_len);
  range_t* right_arr = malloc(sizeof(range_t) * right_len);

  for (int i = 0; i < left_len; i++) {
    left_arr[i] = arr[left + i];
  }

  for (int i = 0; i < right_len; i++) {
    right_arr[i] = arr[mid + 1 + i];
  }

  int index = left;
  int left_index = 0;
  int right_index = 0;

  while (left_index < left_len && right_index < right_len) {
    if (left_arr[left_index].low < right_arr[right_index].low) {
      arr[index++] = left_arr[left_index++];
    } else {
      arr[index++] = right_arr[right_index++];
    }
  }

  while (left_index < left_len) {
    arr[index++] = left_arr[left_index++];
  }
  while (right_index < right_len) {
    arr[index++] = right_arr[right_index++];
  }

  free(left_arr);
  free(right_arr);
}

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
    unsigned long low = strtoul(low_str, NULL, 10);
    unsigned long high = strtoul(high_str, NULL, 10);
    range_t range = {low, high};
    ranges[range_idx++] = range;
  }

  merge_sort(ranges, 0, range_count - 1);
  for (int i = 0; i < range_count; i++) {
    printf("range is %lu-%lu\n", ranges[i].low, ranges[i].high);
  }

  // merge the sorted ranges

  range_t* new_ranges = malloc(sizeof(range_t) * range_count);
  int new_ranges_idx = 0;
  unsigned long current_high = ranges[0].high;
  unsigned long current_low = ranges[0].low;
  for (int i = 1; i < range_count; i++) {
    if (ranges[i].low <= current_high) {
      if (ranges[i].high > current_high) {
        current_high = ranges[i].high;
      }
      continue;
    } else {
      range_t range = {current_low, current_high};
      new_ranges[new_ranges_idx++] = range;
      current_low = ranges[i].low;
      current_high = ranges[i].high;
    }
  }

  range_t r = {current_low, current_high};
  new_ranges[new_ranges_idx] = r;

  unsigned long total = 0;
  for (int i = 0; i < new_ranges_idx; i++) {
    printf("nums in range %lu-%lu are %lu\n", new_ranges[i].low,
           new_ranges[i].high, new_ranges[i].high - new_ranges[i].low + 1);
    total += new_ranges[i].high - new_ranges[i].low + 1;
  }

  printf("total is %lu\n", total);
}
