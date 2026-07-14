#include <stdio.h>
#include <stdlib.h>

// Single-linked list

typedef struct Node {
  int val;
  struct Node *next;
} Node;

int delVal(Node **head, int val);
void insertTail(Node **head, int val);
void printList(Node *head);

int main() {
  // Initializing linked list
  Node *head = NULL;
  int arr[] = {1,2,82734,4,5,6,7};
  int arrSize = sizeof(arr)/sizeof(arr[0]);
  for (int i=0; i < arrSize; i++) {
    insertTail(&head, arr[i]);
  }

  printList(head);

  // test deletion
  if (delVal(&head, 1)) {
    printf("Deleted successfully\n");
  } else {
    printf("Fail to delete\n");
  };

  printList(head);

  return 0;
}

void insertTail(Node **head, int val) {
  if ((*head) == NULL) {
    (*head) = malloc(sizeof(Node));
    (*head)->val = val;
    (*head)->next = NULL;
  } else {
    Node *t = (*head);
    while (t->next != NULL) t = t->next;
    t->next = malloc(sizeof(Node));
    t->next->val = val;
    t->next->next = NULL;
  }
}

int delVal(Node **head, int val) {
  if ((*head) == NULL) {
    return 0;
  } else {
    while ((*head) != NULL) {
      if ((*head)->val == val) {
        (*head) = (*head)->next;
        return 1;
      }
      head = &(*head)->next;
    }
    return 0;
  }
}

void printList(Node *head) {
  if (head == NULL) {
    printf("--Nothing--\n");
    return;
  } else {
    while (head != NULL) {
      printf("%d - ", head->val);
      head = head->next;
    }
    printf("\n");
  }
}