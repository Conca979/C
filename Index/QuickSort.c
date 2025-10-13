#include <stdio.h>
#include <stdlib.h>

void quickSort(int *arr, int arrSize);
void printArr(int arr[], int arrSize);

int main() {
  // int arr[] = {17,13,12,100,8,15,2,16};
  int arr[] = {17,13,12,100,8,15,2,16,0,20,1,3,4,19,20,10,18,7,9,11,5,6,14};
  int *arr2 = malloc(4*sizeof(int));
  arr[0] = 13;
  arr[1] = 8;
  arr[2] = 100;
  arr[3] = 14;
  int arrSize = sizeof(arr)/sizeof(int);
  quickSort(arr2, 4);
  // quickSort(arr, arrSize);

  printf("Sorted: ");
  printArr(arr2, arrSize);
  // printArr(arr, arrSize);

  return 0;
}

void printArr(int arr[], int arrSize) {
  printf("[ ");
  for (int i = 0; i < arrSize; i++) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
}

void quickSort(int *arr, int arrSize) {
  int pivot = arrSize-1;
  int sIndex = 0, bIndex = -1;
  int swap = 0;
  while (sIndex < pivot) {
    if (arr[sIndex] < arr[pivot]) {
      while (bIndex < sIndex) {
        bIndex++;
        if (arr[bIndex] > arr[pivot]) {
          swap = 1;
          break;
        }
      }
      int temp = arr[sIndex];
      arr[sIndex] = arr[bIndex];
      arr[bIndex] = temp;
    }
    sIndex++;
  }
  bIndex++;
  if (arr[bIndex] > arr[sIndex]) {
      int temp = arr[pivot];
      arr[pivot] = arr[bIndex];
      arr[bIndex] = temp;
  } 
  //
  int lSize = bIndex;
  int rSize = arrSize-lSize-1;
  //
  int lArr[lSize];
  for (int i = 0; i<lSize; i++) {
    lArr[i] = arr[i];
  }
  int rArr[rSize];
  for (int i = 0; i<rSize; i++) {
    rArr[i] = arr[lSize+1+i];
  }
  //
  if (lSize > 1) {
    quickSort(lArr, lSize);
  }
  if (rSize > 1) {
    quickSort(rArr, rSize);
  }
  //
  for (int i = 0; i<lSize; i++) {
    arr[i] = lArr[i];
  }
  for (int i = 0; i<rSize; i++) {
    arr[lSize+1+i] = rArr[i];
  }

}