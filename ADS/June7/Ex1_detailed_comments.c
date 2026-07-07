#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>

int main() {
  int N;

  // Ask the user to enter a positive integer.
  printf("N = ");
  scanf("%d", &N);

  // Start checking divisibility from the smallest prime number.
  int divisor = 2;

  // Continue until N has been completely factorized.
  // When N becomes 1, there are no more prime factors.
  while (N != 1) {

    // Check if the current divisor divides N exactly.
    if ((N % divisor) == 0) {

      // The divisor is a prime factor of N.
      printf("%d ", divisor);

      // Remove this factor from N.
      // We do NOT increase divisor here because the same
      // prime factor may appear multiple times.
      // Example: N = 12
      // 12 / 2 = 6
      // 6 / 2 = 3
      N /= divisor;

    } else {

      // The current divisor is not a factor.
      // Try the next possible divisor.
      divisor += 1;
    }
  }

  return 0;
}