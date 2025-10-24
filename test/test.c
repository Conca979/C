// Problem:
// Given a positive natural number N = 3450 we would like to study numbers by:
// Count the number of odd, even digits of N. Note that 0 is even.
// Example:
// The number of odd digits of N = 3450 is 2 with odd digits = {3, 5};
// The number of even digits of N = 3450 is 2 with even digits = {4,0}.
// Question 1: (12 pts)
// Propose two recursive pseudo-code algorithms to count the number of odd and even digits of N (one function for odd, one function for even). (2 pts)
// Implement the proposed algorithms in C/C++. (8pts)
// Calculate the complexity of your program (Best scenario, Worst scenario, Average). Justify your answer. (2 pts)



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lengthOfLastWord(char* s) {
  int sSize = 0, lwSize = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    sSize++;
  }
  for (int i = sSize-1; i >= 0; i--) {
    if (s[i] != ' ') {
      for (int j = i; j >= 0 && s[j] != ' '; j--) {
        lwSize++;
      }
      break;
    }
  }
  return lwSize;
}
char* intToRoman(int num) {
  char symbol[] = "IVXLCDM";
  int numSize = 0, temp = num;
  while (temp != 0) {
    numSize++;
    temp /= 10;
  }
  char *roman = malloc(sizeof(int));
  int romanSize = 0;
  roman[0] = '\0';
  for (int i = 0; i < numSize; i++) {
    int token = num%10;
    if (token < 4) {
      int newSize = romanSize + token;
      roman = realloc(roman, newSize*sizeof(int));
      for (int j = romanSize; j < newSize; j++) {
        romanSize++;
        roman[j] = '\0';
        roman[j-1] = symbol[i*2];
      }
    } else if (token >= 5 && token < 9) {
      int newSize = romanSize + token - 4;
      roman = realloc(roman, newSize*sizeof(int));
      for (int j = romanSize; j < newSize-1; j++) {
        romanSize++;
        roman[j] = '\0';
        roman[j-1] = symbol[i*2];
      }
      roman[romanSize-1] = symbol[i*2+1];
      roman[romanSize] = '\0';
      romanSize++;
    } else { // when toekn = 4 or 9
      int newSize = romanSize + 2;
      romanSize += 2;
      roman = realloc(roman, newSize*sizeof(int));
      roman[newSize-1] = '\0';
      roman[newSize-2] = symbol[i*2];
      roman[newSize-3] = symbol[i*2+(token==4?1:2)];
    }
    num /= 10;
  }
  for (int i = 0; i < (romanSize-1)/2; i++) {
    int temp = roman[i];
    roman[i] = roman[romanSize-2-i];
    roman[romanSize-2-i] = temp;
  }
  return roman;
}
