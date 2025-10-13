#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *arr, int arrSize);
void quickSort(int *arr, int arrSize);
void mergeSort(int *arr, int arrSize);
void insertionSort(int *arr, int arrSize);
void selectionSort(int *arr, int arrSize);
//
void printArr(int *arr, int size);

int main() {
  int arr[] = {
    // --- Smallest to Largest (already sorted segment) ---
    -50, -30, -10, 0, 5, 12, 25, 40,

    // --- Largest to Smallest (reverse sorted segment) ---
    99, 88, 77, 66, 55, 44, 33, 22, 11,

    // --- Duplicates and Zeros ---
    -5, -5, 0, 0, 0, 7, 7, 7, 7, 10, 10,

    // --- Single element & edge values ---
    -100, // Smallest possible value to consider
    1000, // Largest possible value to consider
    -1,   // Just below zero
    1,    // Just above zero

    // --- More mixed values ---
    30, -20, 50, -60, 20, -40, 60, 15, -15,

    // --- An array that is completely identical ---
    // (You might want to test this as a separate array for a very specific edge case)
    // 5, 5, 5, 5, 5, 5,

    // --- Random-like distribution for general testing (add more if needed) ---
    93, 17, 82, 49, 61, 28, 74, 35, 58, 42, 
    10, 20, 30, 40, 50, 60, 70, 80 // Some more ordered ones mixed in
  };
  int arrSize = sizeof(arr)/sizeof(int);
  //
  int *arr2 = malloc(arrSize*sizeof(int));
  for (int i = 0; i < arrSize; i++) {
    arr2[i] = arr[i];
  }
  //
  printf("Orginal: ");
  printArr(arr2, arrSize);

  printf("Sorted: \n");
  selectionSort(arr2, arrSize);
  printArr(arr2, arrSize);
  quickSort(arr, arrSize);
  printArr(arr, arrSize);
  


  return 0;
}

void bubbleSort(int *arr, int arrSize) {
  for (int i = 0; i < arrSize-1; i++) {
    for (int j = 0; j < arrSize-i-1; j++) {
      if (arr[j] > arr[j+1]) {
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}

void printArr(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
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

void insertionSort(int *arr, int arrSize) {
  for (int i = 0; i < arrSize-1; i++) {
    for (int j = i; j >= 0; j--) {
      if (arr[j] > arr[j+1]) {
        int temp = arr[j+1];
        arr[j+1] = arr[j];
        arr[j] = temp;
      } else break;
    }
  }
}

void selectionSort(int *arr, int arrSize) {
  for (int i = 0; i<arrSize-1; i++) {
    int min = arr[i];
    int minIndex = i;
    for (int j = i; j < arrSize; j++) {
      if (arr[j] < min) {
        min = arr[j];
        minIndex = j;
      }
    }
    int temp = min;
    arr[minIndex] = arr[i];
    arr[i] = temp;
  }
}