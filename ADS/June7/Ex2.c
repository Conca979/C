#include <stdio.h>
#include <stdlib.h>

int maxValidPairSum(int* nums, int numsSize, int k);

int main() {
  int arr[] = {1,3,5,2,8}; // max = 13
  int arrSize = sizeof(arr)/sizeof(arr[0]);

  int max = maxValidPairSum(arr, arrSize, 1); 
  
  printf("max = %d", max);

  return 0;
}

int maxValidPairSum(int* nums, int numsSize, int k) {
  int outerMax = 0;
  int innerMax = 0;

  for (int i = k; i < numsSize; i++) {
    if (nums[i-k] > innerMax) {
      innerMax = nums[i-k];
    }
    if ((innerMax + nums[i]) > outerMax) {
      outerMax = innerMax + nums[i];
    }
  }

  return outerMax;
}