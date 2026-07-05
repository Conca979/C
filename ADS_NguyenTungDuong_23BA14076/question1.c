#include <stdio.h>
#include <stdlib.h>

// the complexity: O(a/b)

void div_recursive(int *q, int *r, int a, int b);

int main() {
  int a = 21, b = 5;
  int quotient = 0, remainder = 0;
  if (b == 0) {
    printf("Error: division by zero is not allowed.\n");
    return 1;
  }
  div_recursive(&quotient, &remainder, a, b);
  printf("Result:\n");
  printf("%d / %d = %d (remainder %d)\n", a, b, quotient, remainder);

  return 0;
}

void div_recursive(int *q, int *r, int a, int b) {
  if (a < b) {
      *r = a; 
      return;
  }
  (*q)++;
  div_recursive(q, r, a - b, b);
}
