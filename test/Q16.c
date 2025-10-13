// Problem:
// <!-- In this context, we would like to find all twin primes from a given array of naturals. A twin prime is a prime number that is either 2 less or 2 more than another prime number (p, p + 2 ) or (p + 2, p)
// For example, an array is given (3, 101, 96, 47, 41, 7, 65, 9, 13, 5, 79, 45, 30, 11, 43). The list of twin primes is (3, 5), (7, 5}, {13, 11}, {41, 43).
// Problem 1: (13pts)
// - Write pseudo-code using Recursion (if necessary, Iteration) to find all twin primes (3pts)
// - Write a program in C/C++ to complete your proposed algorithm in the pseudo-code. (8pts).
// : The program must include a recursive function and the main function.
// Note - Calculate the complexity of your algorithm. Justify the answer. (2pts)
// Problem 2: (7pts)
// Rewrite the program in C/C++ using Linked Lists ADT to solve this problem. (4pts)
// Propose a method to improve the complexity of finding twin primes. Explain. (3pts) -->

#include <stdio.h>
#include <stdlib.h>

typedef struct values {
  int value;
  struct values *next;
} values;

void recursion(int arr[], int arrSize, int index1, int index2);
void linkedList(values *head);
int isPrime(int value);
//
void insertValue(values **head, int value);
void printList(values *head);
//

int main() {
  int arr[] = {3, 101, 96, 47, 41, 7, 65, 9, 13, 5, 79, 45, 30, 11, 43};
  int arrSize = sizeof(arr)/sizeof(int);
  //
  // for (int i = 0; i < arrSize-1; i++) {
  //   for (int j = i; j < arrSize; j++) {
  //     if ((arr[i]-arr[j]) == 2 || (arr[i]-arr[j]) == -2) {
  //       printf("(%d,%d)\n", arr[i], arr[j]);
  //     }
  //   }
  // }
  //
  // recursion(arr, arrSize, 0, 1);
  values *head = NULL;
  for (int i = 0; i < arrSize; i++) {
    insertValue(&head, arr[i]);
  }
  printList(head);
  linkedList(head);

  return 0;
}

void recursion(int arr[], int arrSize, int index1, int index2) {
  if (index2 == arrSize) {
    index1++;
    index2 = index1;
  }
  if (index1 == arrSize-1) {
    return;
  } else {
    if ((isPrime(arr[index1]) && isPrime(arr[index2]))) {
      if ((arr[index1]-arr[index2]) == 2 || (arr[index1]-arr[index2]) == -2) {
        printf("(%d,%d)\n", arr[index1], arr[index2]);
      }
    }
  }
  recursion(arr, arrSize, index1, index2+1);
}

void insertValue(values **head, int value) {
  if ((*head) == NULL) {
    (*head) = malloc(sizeof(values));
    (*head)->value = value;
    (*head)->next = NULL;
  } else {
    insertValue(&((*head)->next), value);
  }
}

void printList(values *head) {
  while (head != NULL) {
    printf("%d%c", head->value, head->next==NULL?'.':'-');
    head = head->next;
  }
  printf("\n");
}

void linkedList(values *head) {
  if (head == NULL) {
    return;
  }
  int *arr = malloc(sizeof(int));
  int arrSize = 1;
  arr[0] = head->value;
  head = head->next;
  while (head != NULL) {
    arrSize++;
    arr = realloc(arr, arrSize*sizeof(int));
    arr[arrSize-1] = head->value;
    head = head->next;
  }
  //
  int arr2[arrSize];
  for (int i = 0; i < arrSize; i++) {
    arr2[i] = arr[i];
  }
  recursion(arr2, arrSize, 0, 1);
}

int isPrime(int value) {
  for (int i = 2; i < value-1; i++) {
    if (value%i == 0) {
      return 0;
    }
  }
  return 1;
}