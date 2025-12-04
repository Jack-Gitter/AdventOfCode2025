#define MAX_LEN 12

typedef struct {
  char elems[MAX_LEN];
  int index;
} stack;

stack init_stack();

char pop(stack* s);

char push(stack* s, char to_push);

unsigned long to_num(stack* s);

char peek(stack* s);

int used_space(stack* s);

void print_stack(stack* s);
