#include <stdio.h>
#include <stdlib.h>

// Single-linked list

typedef struct Node {
    int val;
    struct Node *next;
} Node;

void delVal(Node **head, int val);
void insert(Node **head, int val);
void printList(Node *head);
int* max(Node *head);
int* min(Node *head);
int sizeOfList(Node *head);

void main() {
    // Initializing linked list
    Node *head = NULL;
    int arr[] = {1,2,82734,4,5,6,7};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    for (int i=0; i < arrSize; i++) {
        insert(&head, arr[i]);
    }

    // Test insertion
    printList(head);

    // Test min max
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    a = max(head);
    b = min(head);
    if (a == NULL) {
        printf("--Linked list is empty--\n");
    } else {
        printf("Min: %d\n", *b);
        printf("max: %d\n", *a);
    }

    // Test counting
    printf("--Linked List size: %d", sizeOfList(head));
}

void insert(Node **head, int val) {
    if ((*head) == NULL ) {
        (*head) = malloc(sizeof(Node));
        (*head)->val = val;
        (*head)->next = NULL;
    } else if ((*head)->next != NULL) {
        insert(&(*head)->next, val);
    } else {
        (*head)->next = malloc(sizeof(Node));
        (*head)->next->val = val;
        (*head)->next->next = NULL;
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

void delVal(Node **head, int val) {
    if ((*head) == NULL) {
        printf("--No %d left to delete--\n", val);
        return;
    } else {
        if ((*head)->val == val) {
            if ((*head)->next == NULL) {
                (*head) = NULL;
            } else {
                (*head)->val = (*head)->next->val;
                (*head)->next = (*head)->next->next;
            }
        } else {
            delVal(&(*head)->next, val);
        }
    }
}

int* max(Node *head) {
    if (head == NULL) {
        return NULL;
    } else {
        int *a = malloc(sizeof(int));
        int *b = malloc(sizeof(int));
        a = &head->val;
        b = max(head->next);
        if (b == NULL) {
            return a;
        } else {
            return (*a > *b) ? a: b;
        }
    }
}

int* min(Node *head) {
    if (head == NULL) {
        return NULL;
    } else {
        int *a = malloc(sizeof(int));
        int *b = malloc(sizeof(int));
        a = &head->val;
        b = min(head->next);
        if (b == NULL) {
            return a;
        } else {
            return (*a < *b) ? a: b;
        }
    }
}

int sizeOfList(Node *head) {
    int size = 0;
    if (head == NULL) {
        return size;
    } else {
        size++;
    }
    return size + sizeOfList(head->next);
}