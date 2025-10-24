// Binary Search (Recursion vs Iteration)
// Problem:
// Given a sorted array and a target value, find its index using:
// iterative binary search,
// recursive binary search.

#include <stdio.h>

int iteration(int *arr, int arrSize, int num);
int recursion(int *arr, int arrSize, int num);

int main() {
  int arr[] = {4, 15, 45, 9, 40, 27, 3, 5, 10};
  int arrSize = sizeof(arr)/sizeof(int);
  printf("%d\n", iteration(arr, arrSize, 11));
  printf("%d\n", recursion(arr, arrSize, 11));

  return 0;
}

int iteration(int *arr, int arrSize, int num) {
  int index = 0, found = 0;
  for (int i = 0; i < arrSize; i++) {
    if (arr[i] == num) {
      found = 1;
      index = i;
      break;
    }
  }
  if (found) return index;
  else return -1;
}

int recursion(int *arr, int arrSize, int num) {
  if (arrSize == 1) {
    if (arr[arrSize-1] == num) {
      return arrSize-1;
    } else return -1;
  } else { // arrSize >= 2
    if (arr[arrSize-1] == num) {
      return arrSize-1;
    } else {
      return recursion(arr, arrSize-1, num);
    }
  }
}