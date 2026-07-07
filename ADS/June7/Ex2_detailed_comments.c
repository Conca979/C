#include <stdio.h>

// Returns the maximum value of nums[i] + nums[j]
// such that j - i >= k.
int maxValidPairSum(int* nums, int numsSize, int k);

int main() {
  // Valid pairs must have indices at least 1 apart (if k = 3, pairs must be at least 3 apart).
  int k = 1;

  // Example array.
  // The maximum sum is 5 + 8 = 13.
  int arr[] = {1, 3, 5, 2, 8};

  // Compute the number of elements in the array.
  int arrSize = sizeof(arr) / sizeof(arr[0]);

  // Find the maximum valid pair sum.
  int max = maxValidPairSum(arr, arrSize, 1);

  printf("max = %d", max);

  return 0;
}

int maxValidPairSum(int* nums, int numsSize, int k) {

  // Stores the largest valid pair sum found so far.
  int outerMax = 0;

  // Stores the largest value that can legally be paired
  // with the current element.
  //
  // At iteration i, this is the maximum value among:
  // nums[0], nums[1], ..., nums[i-k]
  int innerMax = 0;

  // i represents the second index (j) of the pair.
  // The first possible j is k because j - i >= k.
  for (int i = k; i < numsSize; i++) {

    // nums[i-k] has just become eligible to pair with nums[i].
    // Update the best left-side value seen so far.
    if (nums[i - k] > innerMax) {
      innerMax = nums[i - k];
    }

    // Compute the best possible sum ending at index i.
    if ((innerMax + nums[i]) > outerMax) {
      outerMax = innerMax + nums[i];
    }
  }

  return outerMax;
}