// complexity: for iteration: O(n) with n is the length of the input number
// for recursion: O(n)

#include <stdio.h>
#include <stdlib.h>

void iteration(int number);
void recursion(int number);
//
int loop(int orgin, int number, int *sum); // dont call this function on main;

int main() {
  int number = 12;
  iteration(number);
  recursion(number);

  return 0;
}

void iteration(int number) {
  int sum = 0;
  int temp = number;
  if (number == 0) {
    return;
  } else if (temp < 0) {
    temp = 0-temp;
  }
  while (temp > 0) {
    sum += temp % 10;
    temp /= 10;
  }
  if (number % sum == 0) {
    printf("%d is a Harshed number\n", number);
  } else {
    printf("%d is NOT a Harshed number\n", number);
  }
}

void recursion(int number) {
  int temp = number;
  if (number == 0) {
    printf("%d is a invalid input\n", number);
    return;
  } else if (number < 0) {
    temp = 0-temp;
  }
  int sum = 0;
  // printf("%d-%d", loop(temp, &sum), sum);
  if (loop(temp, temp, &sum) == 1) {
    printf("%d is a Harshed number\n", number);
  } else {
    printf("%d is NOT a Harshed number\n", number);
  }
}

int loop(int orgin, int number, int *sum) {
  if (number == 0) {
    if ((orgin % (*sum)) == 0) {
      return 1;
    } else {
      return 0;
    }
  } else {
    (*sum) += number % 10;
    return loop(orgin, number/10, sum);
  }
}