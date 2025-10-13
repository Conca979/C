#include <stdio.h>
#include <stdlib.h>

// linked list queue implementation

// head of line-> Q1 - Q2 - Q3 - Q4 <- end of line
// by Q2's perspective Q1 is previous, Q3 is next

typedef struct Queue {
  int value;
  struct Queue *prv;
  struct Queue *next;
} Queue;

void enQueue(Queue **head, int value);
void deQueue(Queue **head);
void display(Queue *head);
int length(Queue *head);

int main() {
  Queue *head = NULL;
  enQueue(&head, 3);
  enQueue(&head, 5);
  deQueue(&head);
  enQueue(&head, 999);
  enQueue(&head, 1);
  enQueue(&head, 4);
  display(head);
  printf("%d", length(head));


  return 0;
}

void enQueue(Queue **head, int value) {
  if ((*head) == NULL) {
    (*head) = malloc(sizeof(Queue));
    (*head)->value = value;
    (*head)->next = NULL;
    (*head)->prv = NULL;
  } else {
    Queue *temp = (*head);
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = malloc(sizeof(Queue));
    temp->next->value = value;
    temp->next->next = NULL;
    temp->next->prv = temp;
  }
}

void display(Queue *head) {
  if (head == NULL) return;
  printf("Head of line -> ");
  while (head != NULL) {
    printf("%d %c ", head->value, head->next==NULL?'.':'-');
    head = head->next;
  }
  printf("<- End of line\n");
}

void deQueue(Queue **head) {
  if ((*head) == NULL)
    return;
  (*head) = (*head)->next;
}

int length(Queue *head) {
  int count = 0;
  if (head == NULL) {
    return 0;
  } else {
    count++;
    int temp = length(head->next);
    return count+temp;
  }
}