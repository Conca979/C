// Given an array of 10 elements: 2, 10, 27, 13, 90, 45, 5, 26, 49, 50.
// In this problem, we try to find all co-prime numbers. Two integer numbers are co-prime if the
// greatest common divisor of these two is 1.
// The list of co-prime numbers from the above array is: {(2, 27), (2,13), (2,45), (2,5), (2,49), (10,
// 27), (10, 13), (10,49), (27,13), (27,5), (27,26), (27,50), (13,90), (13,45), (13,5), (13,49), (13,50),
// (90,49), (90,26), (90,49), (45,26), (45,49), (5,26), (5,49), (26,49), (49,50)}
// Question 1: (10 pts)
//  Write a program to find all co-prime numbers with a given array of integer numbers using
// Iteration. (8 pts)
//  Calculate the complexity of your program (Best scenario, Worst scenario, Average). Justify
// your answer. (2 pts)
// Question 2: (6 pts)
// In this context, we try to find co-prime numbers using at least a recursive function.
//  Implement the recursive function (2 pts).
//  Write a program to solve the above Problem using the recursive function (4 pts)
// Question 3: (4 pts)
//  Write a program to solve the Problem using Linked List ADT with necessary functions
// and Linked List principle. (4 pts)
// Note: Each element in the array is presented as a node in the Linked List data structure.

#include <stdio.h>
#include <stdlib.h>

int GCD(int a, int b);
void recursive(int *arr, int arrSize, int index1, int index2);
//
///// for question 3 only
typedef struct node {
  int value;
  struct node *prv;
  struct node *next;
} node;

void insertValue(node **head, int value);
void sortList(node **head);
void checkList(node *node1, node *node2);
void coPrimeList(node *head);
//
void printList(node *head);
/////

int main() {
  int arr[] = { 2, 10, 27, 13, 90, 45, 5, 26, 49, 50};
  int arrSize = sizeof(arr)/sizeof(int);
  //
  // for (int i = 0; i < arrSize-1; i++) {
  //   for (int j = i; j < arrSize; j++) {
  //     if (GCD(arr[i], arr[j])) {
  //       printf("(%d,%d)", arr[i], arr[j]);
  //     }
  //   }
  // }
  ///// question 3
  node *head = NULL;
  for (int i = 0; i < arrSize; i++) {
    insertValue(&head, arr[i]);
  }
  coPrimeList(head);
  /////

  // recursive(arr, arrSize, 0, 1);

  return 0;
}

int GCD(int a, int b) {
  if (a == 0 || b == 0) {
    return 0;
  }
  int min = a>b?b:a;
  int count = 0;
  for (int i = min; i >=1 ; i--) {
    if ((a%i == 0) && (b%i == 0)) {
      count++;
    }
  }
  if (count == 1) {
    return 1;
  } else {
    return 0;
  }
}

void recursive(int *arr, int arrSize, int index1, int index2) {
  if (index2 > arrSize) {
    index1++;
    index2 = index1+1;
    if (index1 > (arrSize-1)) {
      return;
    } else {
      if (GCD(arr[index1], arr[index2])) {
        printf("(%d,%d)", arr[index1], arr[index2]);
      }
    }
    // printf("(%d,%d)", index1, index2);
    return recursive(arr, arrSize, index1, index2+1);
  } else {
    // printf("(%d,%d)", index1, index2);
    if (GCD(arr[index1], arr[index2])) {
      printf("(%d,%d)", arr[index1], arr[index2]);
    }
    return recursive(arr, arrSize, index1, index2+1);
  }
}

/// for linked list in question 3 only
void insertValue(node **head, int value) {
  if ((*head) == NULL) {
    (*head) = malloc(sizeof(node));
    (*head)->value = value;
    (*head)->next = NULL;
    (*head)->prv = NULL;
    return;
  }
  if ((*head)->next != NULL) {
    insertValue(&((*head)->next), value);
  } else {
    (*head)->next = malloc(sizeof(node));
    (*head)->next->value = value;
    (*head)->next->next = NULL;
    (*head)->next->prv = (*head);
  }

}

void printList(node *head) {
  if (head == NULL) 
    return;
  printf("%d ", head->value);
  head = head->next;
  while (head != NULL) {
    printf("%d ", head->value);
    head = head->next;
  }
  printf("\n");
}

void sortList(node **head) {
  if (head == NULL)
    return;
  int arrSize = 1;
  int *arr = malloc(arrSize*sizeof(int));
  arr[0] = (*head)->value;
  node *temp = (*head)->next;
  for (int i = 1; temp != NULL; i++) {
    arrSize++;
    arr = realloc(arr, arrSize*sizeof(int));
    arr[i] = temp->value;
    temp = temp->next;
  }
  //sort 
  for (int i = 0; i < arrSize-1; i++) {
    for (int j = 0; j < arrSize-i; j++) {
      if (arr[j] > arr[j+1]) {
        int temp = arr[j+1];
        arr[j+1] = arr[j];
        arr[j] = temp;
      }
    }
  }
  // for (int i = 0; i < arrSize; i++) {
  //   printf("%d ", arr[i]);
  // }
  (*head) = NULL;
  for (int i = 0; i < arrSize; i++) {
    insertValue(head, arr[i]);
  }
}

void checkList(node *node1, node *node2) {
  if (node2 == NULL) {
    node1 = node1->next;
    node2 = node1->next;
    if (node2 == NULL) {
      return;
    }
    if (GCD(node1->value, node2->value)) {
      printf("(%d,%d)", node1->value, node2->value);
    }
    return checkList(node1, node2->next);
  } else {
    if (GCD(node1->value, node2->value)) {
      printf("(%d,%d)", node1->value, node2->value);
    }
    return checkList(node1, node2->next);
  }
}

void coPrimeList(node *head) {
  checkList(head, head->next);
}