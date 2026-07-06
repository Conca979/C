#include <stdio.h>
#include <stdlib.h>

void main() {
  int _1 = 5;
  int *_2 = &_1;
  int **_3 = &_2;

  printf("%d, %d\n", *_2, **_3);

  *_2 = 0;
  (**_3)++;
  printf("%d", _1);
}