// Problem:
// In this problem, we would like to perform a prime factorization of a given natural number N:
// N = 120 = 2 * 2 * 2 * 3 * 5;
// N = 84 = 2 * 2 * 3 * 7
// Question 1: (12 pts)
// ▪ Write a pseudo-code to implement the factorization using Recursion (combined with
// iteration if necessary). (3 pts)
// ▪ Implement the proposed pseudo-code using C/C++. (7 pts)
// ▪ Calculate the complexity of your program (Best scenario, Worst scenario, Average). Justify
// your answer. (2 pts)
// Question 2: (8 pts)
// We would like to improve the factorization by using Divide and Conquer strategy and Binary
// recusion:
// Step 1: Given a natural number N;
// Step 2: Find two biggest divisors of N denoted by d1, d2;
// Step 3: If a divisor d1 or d2 is not a prime, then call step 1 for d1 or d2, respectively; else
// continue;
// Step 4: If d1 and d2 are both prime then exit;
// ▪ Implement the proposed pseudo-code using C/C++ (6 pts)
// ▪ Calculate the complexity of this algorithm. Justify your answer. (2 pts)

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

void primeNum(int *primes, int length);
int check(int *prime, int index, int number);
void primeFactor(int *prime, int number);
int optimize(int number);

int main() {
  int number = 567;
  int arrSize = optimize(number);
  printf("%d", arrSize);
  int arr[arrSize];
  // primeNum(arr, arrSize);
  // for (int i = 0; i < arrSize; i++) {
  //   printf("%d ", arr[i]);
  // }
  // printf("\n");

  // primeFactor(arr, number);
  


  return 0;
}

void primeNum(int *primes, int length) {
  primes[0] = 2;
  int temp = 2;
  for (int i = 1; i < length; i++) {
    bool found = false;
    temp++;
    for (int j = 0; j < i; j++) {
      if ((temp % primes[j]) == 0)
        break;
      if ((j+1)==i) {
        primes[i] = temp;
        found = true;
        break;
      }
    }
    if (!found) 
      i--;
  }
}

int check(int *prime, int index, int number) {
  if (number % prime[index] == 0) {
    printf("%d ", prime[index]);
    check(prime, index, number/prime[index]);
  } else {
    index++;
    if (prime[index] > number) {
      return 0;
    }
    check(prime, index, number);
  }
  return 1;
}

void primeFactor(int *prime, int number) {
  check(prime, 0, number);
}

int optimize(int number) {
  int arr[30>number?number:30];
  primeNum(arr, 30);
  for (int i = 30; i > 0; i--) {
    if (number % arr[i] == 0) {
      return number/arr[i];
    }
  }
  return number;
}