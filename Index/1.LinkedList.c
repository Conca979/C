#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// (doubly) linked list implemenation

typedef struct node {
  int value;
  struct node *prv;
  struct node *next;
} node;

void insertValue(node **head, int value);
void removeValue(node **head, int value);
void reverseList(node **head, node *nodes);
void sortList(node **head);
//
int countEven(node *head);
int findMax(node *head);
int listSize(node *head);
//
void printList(node *head);


int main() {
  node *head = NULL;
  //
  insertValue(&head, 12);
  insertValue(&head, 2);
  insertValue(&head, 100);
  insertValue(&head, 5);
  insertValue(&head, 10);
  insertValue(&head, 5);
  insertValue(&head, 9);
  insertValue(&head, 60);
  insertValue(&head, 1);
  //
  printf("%d-%d-%d\n", countEven(head), findMax(head), listSize(head));

  //
  sortList(&head);
  printList(head);
  return 0;
}

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

int countEven(node *head) {
  int count = 0;
  if (head == NULL) {
    return count;
  }
  if (head->value % 2 == 0) {
    count++;
  }
  int temp = countEven(head->next);
  return count+temp;
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

void reverseList(node **head, node *nodes) {
  if (nodes == NULL) {
    return;
  }
  node *temp = nodes->next;
  nodes->next = nodes->prv;
  nodes->prv = temp;
  (*head) = nodes;
  reverseList(head, nodes->prv);
}

int findMax(node *head) {
  if (head == NULL)
    return INT_MIN;
  int max = head->value;
  int temp = findMax(head->next);
  return temp>max?temp:max;
}

int listSize(node *head) {
  int count = 0;
  if (head == NULL) {
    return count;
  } else count++;
  int temp = listSize(head->next);
  return temp+count;
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