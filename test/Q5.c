// Given a number, repeatedly sum its digits until only one digit remains.
// Example:
// Input: 9875  
// Step 1: 9+8+7+5 = 29  
// Step 2: 2+9 = 11  
// Step 3: 1+1 = 2  
// Output: 2

#include <stdio.h>

int iteration(int number);
int recursion(int number);

int main() {
  int number = 9999;
  printf("%d\n", iteration(number));
  printf("%d\n", recursion(number));


  return 0;
}

int iteration(int number) {
  int temp = number;
  while (number >= 10) {
    temp = 0;
    while (number != 0) {
      temp += number%10;
      number /= 10;
    }
    number = temp;
  }
  return temp;
}

int recursion(int number) {
  int temp = 0;
  if (number < 10) return number;
  else {
    while (number != 0) {
      temp += number %10;
      number /= 10;
    }
  }
  return recursion(temp);
}