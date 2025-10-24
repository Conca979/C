// In this problem, a natural number is given. The objective is to find a digit and swap its position in the number to obtain the smallest possible value.
// Note: The smallest value must have the same number of digits as in the original value; thus, 0 cannot be used.
// Example: 51029 -> the possible smallest value is 15029 after one swap.
// Propose an algorithm using iteration and implement it in C/C++ to complete the task. (3 pts)
// Propose and implement an alternative algorithm using recursion for this task. (6 pts)

#include <stdio.h>
#include <stdlib.h>

int *numToArr(int number);
int minimalizeIteration(int number);
int minimalizeRecursion(int number);

//
int minRecursion(int *arr, int arrSize, int token);
int sumRecursion(int *arr, int arrSize);
int tenPower(int exp);

int main() {
  int number = 912032;
  printf("%d\n", minimalizeIteration(number));
  printf("%d\n", minimalizeRecursion(number));

  return 0;
}

int minimalizeIteration(int number) {
  int temp1 = number, numLen = 0;
  while (temp1 != 0) {
    numLen++;
    temp1 /= 10;
  }
  if (numLen <= 1) return number;
  int *arr = numToArr(number);
  int min = arr[0], index = 0;
  for (int i = 0; i < numLen; i++) {
    if (arr[i] < min && arr[i] >= 1) {
      min = arr[i];
    }
  }
  min = minRecursion(arr, numLen, arr[0]);
  for (int i = numLen - 1; i >= 0; i--) {
    if (arr[i] == min) {
      index = i;
      break;
    }
  }
  int temp = arr[0];
  arr[0] = min;
  arr[index] = temp;
  temp = 0;
  for (int i = 0; i < numLen; i++) {
    temp = temp*10 + arr[i];
  }
  return temp;
}

int minRecursion(int *arr, int arrSize, int token) {
  int min = token;
  if (arrSize >= 1) {
    if (arr[arrSize-1] > 0) min = min>arr[arrSize-1]?arr[arrSize-1]:min;
  } else {
    return min;
  }
  return minRecursion(arr, arrSize-1, min);
}

int *numToArr(int number) {
  int temp = number, numLen = 0;
  while (temp != 0) {
    numLen++;
    temp /= 10;
  }
  int *arr = malloc(numLen*sizeof(int));
  for (int i = 0; i < numLen; i++) {
    arr[i] = number%10;
    number /= 10;
  }
  for (int i = 0; i < numLen/2; i++) {
    int temp = arr[i];
    arr[i] = arr[numLen-1-i];
    arr[numLen-1-i] = temp;
  }
  return arr;
}

int minimalizeRecursion(int number) {
  int temp1 = number, numLen = 0;
  while (temp1 != 0) {
    numLen++;
    temp1 /= 10;
  }
  if (numLen <= 1) return number;
  int *arr = numToArr(number);
  int index = 0, min = minRecursion(arr, numLen, arr[0]);
  for (int i = numLen - 1; i >= 0; i--) {
    if (arr[i] == min) {
      index = i;
      break;
    }
  }
  int temp = arr[0];
  arr[0] = min;
  arr[index] = temp;
  for (int i = 0; i < numLen/2; i++) {
    int temp = arr[i];
    arr[i] = arr[numLen-1-i];
    arr[numLen-1-i] = temp;
  }
  return sumRecursion(arr, numLen);
}

int sumRecursion(int *arr, int arrSize) {
  if (arrSize == 0) return 0;
  return arr[arrSize-1]*tenPower(arrSize-1) + sumRecursion(arr, arrSize-1);
}

int tenPower(int exp) {
  if (exp == 0) return 1;
  return 10*tenPower(exp-1);
}