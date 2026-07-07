#include <stdio.h>
#include <stdlib.h>

int main() {
  int N;
  printf("N = ");
  scanf("%d", &N);

  int divisor = 2;
  while (N != 1) {
    if ((N % divisor) == 0) {
      printf("%d ", divisor);
      N /= divisor;
    } else {
      divisor += 1;
    }
  }

  return 0;
}