#include <stdio.h>
#include <stdlib.h>

// dynamic array-based stack

typedef struct Stack {
  int top; // current size of stack
  int capacity; // stack's size limit
  int *arr;
} Stack;

//
void sInit(Stack **s, int cap);
void push(Stack *s, int value);
void pop(Stack *s);
int top(Stack *s);
//
void printStack(Stack *s);
//

int main() {
  Stack *stack = NULL;
  sInit(&stack, 10);
  push(stack, 23);
  push(stack, 1);
  push(stack, 10);
  push(stack, 1);
  push(stack, 20);
  //
  printStack(stack);
  printf("%d", top(stack));


  return 0;
}

void sInit(Stack **s, int cap) {
  (*s) = malloc(sizeof(Stack));
  // int *arr = malloc(sizeof(int)*cap);
  (*s)->arr = malloc(sizeof(int)*cap);
  (*s)->capacity = cap;
  (*s)->top = 0;

}

void push(Stack *s, int value) {
  if (s->top == s->capacity) {
    printf("Cannot add %d into stack, stack is full\n", value);
    return;
  }
  s->arr[s->top] = value;
  s->top++;
}

void printStack(Stack *s) {
  printf("Stack from top->bottom: ");
  int size = s->top;
  int *arr = s->arr;
  for (int i = size-1; i >= 0; i--) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void pop(Stack *s) {
  if (s->top == 0)
    return;
  s->top--;
}

int top(Stack *s) {
  return s->arr[s->top-1];
}