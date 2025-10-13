// Selection Sort
// The algorithm divides the input list into two parts: the sublist
// of elements already sorted and the unsorted sublist of
// elements remaining to be sorted.
// ▶ The algorithm proceeds by:
// ▶ find the smallest element in the unsorted sublist
// ▶ swap this element with the leftmost unsorted element, it
// equivalents to move this element from the unsorted sublist to
// the sorted one,
// ▶ continue to proceed with all elements in the unsorted sublist

#include <stdio.h>

void seletionSort(int *arr, int arrSize);

int main() {
  int arr[] = {17,13,12,100,8,15,2,16,14,1,3,4,19,20,10,18,7,9,11,5,6,0};
  int arrSize = sizeof(arr)/sizeof(int);
  int index = 0;
  //
  seletionSort(arr, arrSize);
  //
  //print out
  for (int i = 0; i<arrSize; i++) {
    printf("%d ", arr[i]);
  }

  return 0;
}

void seletionSort(int *arr, int arrSize) {
  int index = 0;
  for (int i = 0; i<arrSize-1; i++) {
    int min = arr[index];
    int minIndex = index;
    for (int j = index; j < arrSize; j++) {
      if (arr[j] < min) {
        min = arr[j];
        minIndex = j;
      }
    }
    int temp = min;
    arr[minIndex] = arr[index];
    arr[index] = temp;
    index++;
  }
}