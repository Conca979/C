// graph implementation

#include <stdio.h>
#include <stdlib.h>

// directed graph 
// implementing using adjacency list

typedef struct Graph {
  struct Vertex *arr; // pointer to array of vertices
  int Vsize;
} Graph;

typedef struct Vertex {
  int value;
  struct Edge *edges; // pointer to edge struct
  int Esize;
} Vertex;

typedef struct Edge {
  int to;
  int w;
  struct Edge *next; // pointer to next edge
} Edge;

typedef struct Queue {
  int value;
  int level;
  struct Queue *next;
} Queue;

//
void graphInit(Graph *graph);
void insertEdge(Graph *graph, int scr, int des, int w);
void insertVertex(Graph *graph, int value);
void displayGraph(Graph graph);
void vertexInit(Graph *graph);
void edgeInit (Graph *graph);
//
void enQueue(Queue **queue, int value, int level);
void deQueue(Queue **queue);
void printQueue(Queue *queue);
//
void depth1Search(Graph graph, int scr, int des); //returns all visited nodes
void stacking(Graph graph, Queue **queue, int scr, int des, int level); //returns all visited nodes
//
int main() {
  //
  Graph graph1d;
  Queue *queue = NULL;
  //
  graphInit(&graph1d);
  vertexInit(&graph1d);
  edgeInit(&graph1d);
  displayGraph(graph1d);
  //
  enQueue(&queue, 23, 0);
  enQueue(&queue, 2, 0);
  enQueue(&queue, 45, 0);
  enQueue(&queue, 10, 0);
  enQueue(&queue, 2, 0);
  enQueue(&queue, 10, 0);
  printQueue(queue);
  //
  depth1Search(graph1d, 0, 6);
  
  return 0;
}

  // printf("----------\n");

void vertexInit(Graph *graph) {
  insertVertex(graph, 0);
  insertVertex(graph, 1);
  insertVertex(graph, 2);
  insertVertex(graph, 3);
  insertVertex(graph, 4);
  insertVertex(graph, 5);
  insertVertex(graph, 6);
  insertVertex(graph, 7);
}

void edgeInit (Graph *graph) {
  insertEdge(graph, 0, 2, 3);
  insertEdge(graph, 0, 1, 4);
  insertEdge(graph, 1, 3, 2);
  insertEdge(graph, 1, 6, 7);
  insertEdge(graph, 1, 2, 1);
  insertEdge(graph, 2, 3, 4);
  insertEdge(graph, 2, 4, 2);
  insertEdge(graph, 3, 5, 1);
  insertEdge(graph, 4, 5, 3);
  insertEdge(graph, 4, 7, 5);
  insertEdge(graph, 5, 6, 2);
  insertEdge(graph, 6, 7, 1);
}

void graphInit(Graph *graph) {
  graph->Vsize = 0;
  graph->arr = NULL;
}

void insertVertex(Graph *graph, int value) {
  for (int i = 0; i < graph->Vsize; i++) {
    if (graph->arr[i].value == value) {
      printf("(!) The vertex %d has existed, skipping insertion\n", value);
      return;
    }
  }
  graph->Vsize++;
  graph->arr = realloc(graph->arr, graph->Vsize*sizeof(Vertex));
  graph->arr[graph->Vsize-1].value = value;
  graph->arr[graph->Vsize-1].Esize = 0;
  graph->arr[graph->Vsize-1].edges = NULL;
}

void insertEdge(Graph *graph, int scr, int des, int w) {
  int index = 0;
  int exist = 0;
  for (int i = 0; i < graph->Vsize; i++) {
    if (graph->arr[i].value == scr) {
      index = i;
      exist += 1;
    }
    if (graph->arr[i].value == des) {
      exist += 1;
    }
  }
  if (exist != 2) {
    printf("(!) Vertex %d or %d not found\n", scr, des);
    return;
  }
  Vertex *vertex = &(graph->arr[index]);
  exist = 0;
  //
  if (vertex->Esize == 0) {
    vertex->Esize = 1;
    vertex->edges = malloc(sizeof(Edge));
    vertex->edges->to = des;
    vertex->edges->w = w;
    vertex->edges->next = NULL;
    printf("~ An edge (%d,%d) was added successfully\n", vertex->value, des);
  } else {
    Edge *temp = vertex->edges;
    while (temp != NULL) {
      if (temp->to == des) {
        exist = 1;
        break;
      }
      temp = temp->next;
    }
    if (exist) {
      printf("(!) there already an edge (%d,%d)\n", vertex->value, des);
      return;
    }
    //
    vertex->Esize++;
    temp = vertex->edges;
    while (temp->next != NULL)
      temp = temp->next;
    temp->next = malloc(sizeof(Edge));
    temp->next->to = des;
    temp->next->w = w;
    temp->next->next = NULL;
    printf("~ An edge (%d,%d) was added successfully\n", vertex->value, des);
  }
}

void displayGraph(Graph graph) {
  printf("----------\n");
  for (int i = 0; i < graph.Vsize; i++) {
    Vertex vertex = graph.arr[i];
    printf("[%d]", vertex.value);
    Edge *temp = vertex.edges;
    while (temp != NULL) {
      printf("-(%d,%d)", temp->to, temp->w);
      temp = temp->next;
    }
    printf("\n");
  }
  printf("----------\n");
}

void enQueue(Queue **queue, int value, int level) {
  if ((*queue) == NULL) {
    (*queue) = malloc(sizeof(Queue));
    (*queue)->level = level;
    (*queue)->value = value;
    (*queue)->next = NULL;
  } else {
    Queue *temp = (*queue);
    if (temp->value == value) {
      return;
    }
    while (temp->next != NULL) {
      temp = temp->next;
      if (temp->value == value) {
        return;
      }
    }
    temp->next = malloc(sizeof(Queue));
    temp->next->level = level;
    temp->next->value = value;
    temp->next->next = NULL;
    }
}

void deQueue(Queue **queue) {
  if ((*queue) == NULL) {
    return;
  } else {
    Queue *temp = (*queue);
    (*queue) = (*queue)->next;
    free(temp);
  }
}

void printQueue(Queue *queue) {
  if (queue == NULL) {
    return;
  } else {
    Queue *temp = queue;
    while (temp != NULL) {
      printf("[%d|%d]%c", temp->value, temp->level, (temp->next)==NULL?'.':'-');
      temp = temp->next;
    }
  }
  printf("\n----------\n");
}

void stacking(Graph graph, Queue **queue, int scr, int des, int level) {
  int index = 0, then = 0;
  if (scr == des)
    return;
  for (int i = 0; i < graph.Vsize; i++) {
    if (graph.arr[i].value == scr) {
      index = i;
      then = 1;
      break;
    }
  }
  if (!then) {
    printf("Vertex %d not exist, skip the search\n", scr);
    return;
  }
  Edge *temp = graph.arr[index].edges;
  while (temp != NULL) {
    printf("%d-", temp->to);
    enQueue(queue, temp->to, level);
    stacking(graph, queue, temp->to, des, level+1);
    temp = temp->next;
  }
}

void depth1Search(Graph graph, int scr, int des) {
  Queue *queue = NULL;
  stacking(graph, &queue, scr, des, 1);
  printf("\n");
  printQueue(queue); // = [2|1]-[3|2]-[5|3]-[6|4]-[4|2]-[7|3]-[1|1]. => shortest traversal to 7 is 3
}