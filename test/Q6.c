// Compute the sum of all elements in a 2D matrix (size n×m).
// Example:
// Input: 
// 1 2 3
// 4 5 6
// Output: 21

#include <stdio.h>

int sumIteration(int nums[][4], int rows);
int sumRecursion(int nums[][4], int rows);
int loop(int nums[][4], int rows, int columns, int token1, int token2);

int main() {
  int nums[][4] = {{1,2,3,4},{5,6,7,8}};
  int rows = sizeof(nums)/(4*sizeof(int));

  printf("%d\n", sumIteration(nums, rows));
  printf("%d\n", sumRecursion(nums, rows));
  

  return 0;
}

int sumIteration(int nums[][4], int rows) {
  int sum = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 4; j++) {
      sum += nums[i][j];
    }
  }
  return sum;
}

int sumRecursion(int nums[][4], int rows) {
  return loop(nums, rows, 4, 0, 0);
}

int loop(int nums[][4], int rows, int columns, int token1, int token2) {
  if (token2 >= columns) {
    token1++;
    token2 = 0;
    if (token1 >= rows) {
      return 0;
    }
  }
  return nums[token1][token2] + loop(nums, rows, columns, token1, token2+1);
}