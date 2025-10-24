// In this problem, the objective is to verify whether a set of 3 values is a Pythagorean triple. A
// Pythagorean triple is a set of 3 positive numbers, which are expressed as a2 + b2 = c2
// .
// Example:
// - (3, 5, 4) is a Pythagorean triple, 32 + 42 = 52
// .
// - (10, 8, 6) is a Pythagorean triple, 62 + 82 = 102
// .
// - (6, 8, 13) is not a Pythagorean triple.
// Question 1 (12 pts)
// ▪ Write a pseudo-code to find all Pythagorean triples from a given arr using Iteration. (2pts)
// ▪ Implement your proposed algorithm in C/C++. You have to initialize a random arr (any
// size ≥ 6, any value) in the main() function. (8pts)
// ▪ Calculate the complexity of your algorithm. Justify the answer (comment directly in your
// source files). (2pts)
// Question 2 (8 pts)
// ▪ Propose another algorithm using recursive functions and implement in C/C++ to perform the
// above problem. (6pts)
// ▪ Calculate the complexity of your algorithm. Justify the answer (comment directly in your
// source files). (2pts)

#include <stdio.h>
#include <stdlib.h>


int count = 0;
void recursive(int a, int b, int c, int arrSize);

int arr[] = {17,13,12,8,15,2,16,14,1,3,4,19,20,10,18,7,9,11,5,6};

int main() {
  int arrSize = sizeof(arr)/sizeof(int);
  //
  //bubble sort
  for (int i = 1; i<arrSize; i++) {
    for (int j = 0; j < arrSize-i; j++) {
      if (arr[j]>arr[j+1]) {
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }

  for (int i = 0; i<arrSize; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  recursive(0, 1, 2, arrSize);

  //
  // for (int i = 0; i < arrSize - 2; i++) {
  //   for (int j = i+1; j<arrSize - 1; j++) {
  //     for (int k = j+1; k<arrSize; k++) {
  //       if ((arr[i]*arr[i] + arr[j]*arr[j]) == arr[k]*arr[k]) {
  //         printf("A Pythagorean triple: %d-%d-%d\n", arr[i], arr[j], arr[k]);
  //       // } else {
  //       //   printf("Not a Pythagorean triple: %d+%d != %d\n", arr[i]*arr[i], arr[j]*arr[j], arr[k]*arr[k]);
  //       }
  //     }
  //   }
  // }
  
  return 0;
}

void recursive(int a, int b, int c, int arrSize) {
  // printf("%d-%d-%d  |  ", a, b, c);
  
  if (c == arrSize) {
    b++;
    c = b;
    if (b == (arrSize-1)) {
      a++;
      b = a+1;
      c = b;
      if (a == (arrSize-2)) {
        return;
      }
    }
  } else {
    if ((arr[a]*arr[a]+arr[b]*arr[b]) == arr[c]*arr[c]) {
      printf("A Pythagorean triple: %d-%d-%d\n", arr[a], arr[b], arr[c]);
    }
  }
  return recursive(a, b, c+1, arrSize);
}