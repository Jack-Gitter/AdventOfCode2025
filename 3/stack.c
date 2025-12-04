#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 12

typedef struct {
  char elems[MAX_LEN];
  int index;
} stack;

stack init_stack() {
  stack s = {};
  s.index = 0;
  return s;
}

char pop(stack* s) {
  if (s->index == 0) {
    return s->elems[s->index];
  }
  return s->elems[s->index--];
}

void print_stack(stack* s) {
  char str[13];
  memcpy(str, s->elems, 12);
  str[12] = '\0';
  printf("%s\n", str);
}

char push(stack* s, char to_push) {
  if (s->index == MAX_LEN - 1) {
    perror("stack overflow");
    exit(EXIT_FAILURE);
  }

  s->elems[++s->index] = to_push;
  return to_push;
}

char peek(stack* s) { return s->elems[s->index]; }

int used_space(stack* s) { return s->index + 1; }

unsigned long to_num(stack* s) { return strtoul(s->elems, NULL, 10); }
