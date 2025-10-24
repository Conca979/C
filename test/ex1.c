// Problem:
// Check whether a number or string is a palindrome using recursion and iteration.
// Example:
// Input: 12321 → Palindrome
// Input: 12341 → Not palindrome

#include <stdio.h>
#include <stdlib.h>

int *numToArr(int number);
int iteration(int number);
int recursion(int number);
int loop(int *arr, int left, int right);

int main() {
  int number = 12;
  printf("%d\n", iteration(number));
  printf("%d", recursion(number));


  return 0;
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

int iteration(int number) {
  int *arr = numToArr(number);
  int temp1 = number, numLen = 0;
  while (temp1 != 0) {
    numLen++;
    temp1 /= 10;
  }
  int left = 0, right = numLen - 1;
  while (left < numLen) {
    if (arr[left] != arr[right]) break;
    else {
      left++,
      right--;
    }
  }
  if (left < right) return 0;
  else return 1;
}

int recursion(int number) {
  int *arr = numToArr(number);
  int temp1 = number, numLen = 0;
  while (temp1 != 0) {
    numLen++;
    temp1 /= 10;
  }
  return loop(arr, 0, numLen-1);
}

int loop(int *arr, int left, int right) {
  if (arr[left] != arr[right]) {
    return 0;
  }
  if (left >= right) return 1;
  else { // left <= right 
    return loop(arr, left+1, right-1);
  }
}