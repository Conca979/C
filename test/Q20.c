// let a priority queue of elements
// typedef struct {
// int data;
// int priority; // possible value [0:5]}
// Element;
//typedef struct {
// int size;
// Elemeent elements[100];
//} Queue;
// implement the following functions
// init() to initialize the queue and create an initial queue with at least 6 elements (data, priority)
// enqueue(), dequeue(), display() to add, remove and display the queue

#include <stdio.h>

#define MAX 100

typedef struct {
    int data;
    int priority; // 0 (highest) to 5 (lowest)
} Element;

// Define the queue structure
typedef struct {
    int size;
    Element elements[MAX];
} Queue;

// Function prototypes
void init(Queue *q);
void enqueue(Queue *q, int data, int priority);
Element dequeue(Queue *q);
void display(Queue q);

void init(Queue *q) {
    q->size = 0;

    enqueue(q, 10, 2);
    enqueue(q, 20, 5);
    enqueue(q, 30, 1);
    enqueue(q, 40, 3);
    enqueue(q, 50, 0);
    enqueue(q, 60, 4);
}

void enqueue(Queue *q, int data, int priority) {
    if (q->size >= MAX) {
        printf("Queue is full!\n");
        return;
    }

    Element newElement;
    newElement.data = data;
    newElement.priority = priority;

    int i = q->size - 1;
    while (i >= 0 && q->elements[i].priority > priority) {
        q->elements[i + 1] = q->elements[i];
        i--;
    }

    q->elements[i + 1] = newElement;
    q->size++;
}

Element dequeue(Queue *q) {
    Element removed = { -1, -1 };

    if (q->size == 0) {
        printf("Queue is empty!\n");
        return removed;
    }

    removed = q->elements[0];

    for (int i = 1; i < q->size; i++) {
        q->elements[i - 1] = q->elements[i];
    }
    q->size--;

    return removed;
}

void display(Queue q) {
    if (q.size == 0) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Data\tPriority\n");
    printf("-----------------\n");
    for (int i = 0; i < q.size; i++) {
        printf("%d\t%d\n", q.elements[i].data, q.elements[i].priority);
    }
}

int main() {
    Queue q;
    init(&q);

    printf("Initial queue:\n");
    display(q);

    printf("\nEnqueueing element (data=70, priority=1)...\n");
    enqueue(&q, 70, 1);
    display(q);

    printf("\nDequeuing highest priority element...\n");
    Element e = dequeue(&q);
    printf("Dequeued: data=%d, priority=%d\n\n", e.data, e.priority);
    display(q);

    return 0;
}

