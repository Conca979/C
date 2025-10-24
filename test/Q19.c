// Question 1: (13 pts)
// ▪ Propose a pseudo-code to solve the above problem using Iteration. (2 pts)
// ▪ Implement the proposed algorithms in C/C++. (9pts)
// ▪ Calculate the complexity of your program (Best scenario, Worst scenario, Average). Justify
// your answer. (2 pts)
// Question 2: (6 pts)
// ▪ Implement the Question 1 using Recursion (combined with iteration if necessary). (6pts)

#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *arr, int arrSize);
void iteration(int *arr, int arrSize);
//
void recursion(int *arr, int arrSize);
void loop(int *arr, int arrSize, int i, int j, int k);
//

int main() {
  int arr[] = {4, 15, 45, 9, 40, 27, 3, 5, 10};
  int arrSize = sizeof(arr)/sizeof(int);
  mergeSort(arr, arrSize);
  //
  iteration(arr, arrSize);
  printf("-----\n");
  recursion(arr, arrSize);


  return 0;
}

void mergeSort(int *arr, int arrSize) {
  if (arrSize < 2) return;
  int leftSize = arrSize/2;
  int rightSize = arrSize - leftSize;
  //
  // spliting 
  int leftArr[leftSize];
  for (int i = 0; i < leftSize; i++) {
    leftArr[i] = arr[i];
  }
  int rightArr[rightSize];
  for (int i = 0; i < rightSize; i++) {
    rightArr[i] = arr[leftSize+i];
  }
  //
  if (leftSize > 1) {
    mergeSort(leftArr, leftSize);
  }
  if (rightSize > 1) {
    mergeSort(rightArr, rightSize);
  }
  //
  //sort
  int leftIndex = 0, rightIndex = 0, arrIndex = 0;
  while ((leftIndex < leftSize) && (rightIndex < rightSize)) {
    if (leftArr[leftIndex] <= rightArr[rightIndex]) {
      arr[arrIndex] = leftArr[leftIndex];
      leftIndex++;
      arrIndex++;
    } else {
      arr[arrIndex] = rightArr[rightIndex];
      rightIndex++;
      arrIndex++;
    }
  }
  for (int i = 0; leftIndex < leftSize; i++) {
    arr[arrIndex+i] = leftArr[leftIndex];
    leftIndex++;
  }
  for (int i = 0; rightIndex < rightSize; i++) {
    arr[arrIndex+i] = rightArr[rightIndex];
    rightIndex++;
  }
}

void iteration(int *arr, int arrSize) {
  if (arrSize <= 3) return;
  for (int i = arrSize - 1; i >= 0; i--) {
    for (int j = i - 1; j > 0; j--) {
      for (int k = j - 1; k >= 0; k--) {
        if (arr[i] == arr[j]*arr[k]) {
          printf("(%d, %d, %d)\n", arr[i], arr[j], arr[k]);
        }
      }
    }
  }
}

void recursion(int *arr, int arrSize) {
  if (arrSize <= 3) return;
  loop(arr, arrSize, arrSize-1, arrSize-2, arrSize-3);
}

void loop(int *arr, int arrSize, int i, int j, int k) {
  int shifting = 0;
  if (k < 0) {
    shifting = 1;
    j--;
    k = j;
    if (j < 1) {
      i--;
      j = i - 1;
      k = j;
      if (i < 2) {
        return;
      }
    }
  } else {
    if (arr[i] == arr[j]*arr[k]) {
      printf("(%d, %d, %d)\n", arr[i], arr[j], arr[k]);
    }
  }
  loop(arr, arrSize, i, j, k-1);
}