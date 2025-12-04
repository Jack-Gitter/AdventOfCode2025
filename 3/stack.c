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
  s.index = -1;
  return s;
}

char pop(stack* s) {
  if (s->index == -1) {
    fprintf(stderr, "stack underflow\n");
    exit(EXIT_FAILURE);
  }
  return s->elems[s->index--];
}

void push(stack* s, char to_push) {
  if (s->index == MAX_LEN - 1) {
    fprintf(stderr, "stack overflow\n");
    exit(EXIT_FAILURE);
  }
  s->elems[++s->index] = to_push;
}

void print_stack(stack* s) {
  char str[13];
  memcpy(str, s->elems, s->index + 1);
  str[s->index + 1] = '\0';
  printf("stack is: %s\n", str);
}

char peek(stack* s) {
  if (s->index == -1) {
    fprintf(stderr, "peek on empty stack\n");
    exit(EXIT_FAILURE);
  }
  return s->elems[s->index];
}

int used_space(stack* s) { return s->index + 1; }

unsigned long long to_num(stack* s) {
  char str[13];
  memcpy(str, s->elems, s->index + 1);
  str[s->index + 1] = '\0';
  return strtoul(str, NULL, 10);
}
