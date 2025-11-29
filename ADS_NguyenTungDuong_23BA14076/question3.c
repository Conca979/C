#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int value;
  struct node *prtNode;
  struct node *lcNode;
  struct node *rcNode;
} node;

// LOT : level of traversal
// VLOT: value in level of traversal
// VsLOT: values in level of traversal

void addNode(node **root, int value);
void delNode(node **root, int value);
//
node *findNode(node *root, int value);
int minNode(node *tree);
int maxNode(node *tree);
int VLOT(node *tree, node *root, int LOT, int min);
int *VsLOT(node *tree, int LOT);
void inserTree(node *root, int **arr, int *size);
//
void leftCount(node *root, int value, int *count);
int count(node *root, int value);
int spacing(node *tree, int value);
int numLength(int value);
//
int maxLOT(node *root);
void prtLOTarr(int *arr);
void printTreeFromLargestToSmallest(node *root);
void printTreeVisual(node *tree);
void printSubTree(int value);
void treeTraversal(node *root);
// void printTreeShape(node *root, int space);

node *tree = NULL;
int main() {
  int arr[] = {20, 6, 32, 2, 27, 110, 27, 22};
  int arrSize = sizeof(arr)/sizeof(int);
  // printf("%d", arrSize);

  for (int i = 0; i < arrSize; i++) {
    addNode(&tree, arr[i]);
  }

  printf("Print Tree visual: ");
  printTreeVisual(tree);
  printf("Print Tree from larest to smallest by process right-node-left: ");
  printTreeFromLargestToSmallest(tree);
  printf("\n");
  printf("Node-right-left Traversal process: ");
  treeTraversal(tree);

  return 0;
}

void addNode(node **root, int value) {
  if ((*root) == NULL) {
    // printf("~The root added\n");
    (*root) = malloc(sizeof(node));
    (*root)->value = value;
    (*root)->prtNode = NULL;
    (*root)->lcNode = NULL;
    (*root)->rcNode = NULL;
  } else {
    //
    if (((*root)->value > value) && (*root)->lcNode != NULL) {
      addNode(&(*root)->lcNode, value);
    } else if (((*root)->value > value) && (*root)->lcNode == NULL) {
      node *temp = malloc(sizeof(node));
      temp->value = value;
      temp->prtNode = (*root);
      temp->lcNode = NULL;
      temp->rcNode = NULL;
      (*root)->lcNode = temp;
      // printf("New node was added\n");
    }
    //
    if (((*root)->value < value) && (*root)->rcNode != NULL) {
      addNode(&(*root)->rcNode, value);
    } else if (((*root)->value < value) && (*root)->rcNode == NULL ) {
      node *temp = malloc(sizeof(node));
      temp->value = value;
      temp->prtNode = (*root);
      temp->lcNode = NULL;
      temp->rcNode = NULL;
      (*root)->rcNode = temp;
      // printf("New node was added\n");
    }
  }
}

void printTreeFromLargestToSmallest(node *root) {
  if (root == NULL) {
    return;
  } else {
    // printf("Represent tree in pre-order NLR: ");
    printTreeFromLargestToSmallest(root->rcNode);
    printf("%d-", root->value);
    printTreeFromLargestToSmallest(root->lcNode);
  }
}

void treeTraversal(node *root) {
  if (root == NULL) {
    return;
  } else {
    // printf("Represent tree in pre-order NLR: ");
    printf("%d-", root->value);
    treeTraversal(root->rcNode);
    treeTraversal(root->lcNode);
  }
}

node *findNode(node *root, int value) {
  node *temp = root;
  if (temp == NULL) {
    return NULL;
  } else if (temp->value == value) {
    return temp;
  }
  //
  if (temp->lcNode != NULL) {
    // printf("Left traversl\n");
    node *temp2 = findNode(temp->lcNode, value);
    if (temp2 != NULL) {
      return temp2;
    }
  }
  if (temp->rcNode != NULL) {
    // printf("Right traversl\n");
    node *temp2 = findNode(temp->rcNode, value);
    if (temp2 != NULL) {
      return temp2;
    }
  }
  return NULL;
}

int count(node *root, int value) {
  int count = 0;
  leftCount(root, value, &count);
  return count-1;
}

void leftCount(node *root, int value, int *count) {
  if (root == NULL) {
    return;
  }
  if (root->value <= value) {
    (*count)++;
  }
  // printf("Represent tree in pre-order NLR: ");
  leftCount(root->lcNode, value, count);
  leftCount(root->rcNode, value, count);
}

int maxLOT(node *root) {
  if (root == NULL) {
    return -1;
  }
  int lCount = maxLOT(root->lcNode);
  int rCount = maxLOT(root->rcNode);
  return (lCount > rCount ? lCount : rCount) + 1;
}

int minNode(node *tree) {
  if (tree == NULL) {
    return -2147483648;
  } else if (tree->lcNode == NULL) {
    return tree->value;
  } else {
    node *temp = tree;
    while (temp->lcNode != NULL) {
      temp = temp->lcNode;
    }
    return temp->value;
  }
}

int maxNode(node *tree) {
  if (tree == NULL) {
    return 2147483647;
  } else if (tree->rcNode == NULL) {
    return tree->value;
  } else {
    node *temp = tree;
    while (temp->rcNode != NULL) {
      temp = temp->rcNode;
    }
    return temp->value;
  }
}

int VLOT(node *tree, node *root, int LOT, int min) {
  if (LOT == 0) {
    if (root->value >= min) {
      return root->value;
    } else {
      return minNode(tree)-2;
    }
  } else {
    if (root->lcNode != NULL) {
      int temp = VLOT(tree, root->lcNode, LOT-1, min);
      if (temp > min) {
        return temp;
      }
    }
    if (root->rcNode != NULL) {
      int temp = VLOT(tree, root->rcNode, LOT-1, min);
      if (temp > min) {
        return temp;
      }
    } else {
      return minNode(tree)-2;
    }
  }
}

int *VsLOT(node *tree, int LOT) {
  int *arr = malloc(sizeof(int));
  int count = 0;
  int temp = minNode(tree)-1;
  int value = VLOT(tree, tree, LOT, temp);
  for (int i = 0; value >= temp; i++) {
    arr = realloc(arr, (i+2)*sizeof(int));
    count++;
    arr[i+1] = value;
    value = VLOT(tree, tree, LOT, value+1);
  }
  arr[0] = count;
  return arr;
}

void prtLOTarr(int *arr) {
  int *values = arr;
  int length = values[0];
  for (int i = 1; i <= length; i++) {
    printf("%d ", values[i]);
  }
}

int spacing(node *tree, int value) {
  int shilf = numLength(maxNode(tree));
  return count(tree, value)*shilf+shilf ;
}

void printTreeVisual(node *tree) {
  if (tree == NULL) {
    return;
  }
  printf("\n");
  int shilf = numLength(maxNode(tree));
  for (int i = 0; i <= maxLOT(tree); i++) {
    int *values = VsLOT(tree, i);
    // prtLOTarr(values);
    int length = values[0];
    int space = count(tree, values[length])*shilf+shilf;
    for (int j = 1; j <= space; j++) {
      int numb, found = 0;
      for (int k = 1; k <= length; k++) {
        if (j == spacing(tree, values[k])) {
          numb = values[k];
          found = 1;
        }
      }
      if (found) {
        printf("%d", numb);
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

int numLength(int value) {
  int count = 0;
  while (value > 0) {
    value /= 10;
    count++;
  }
  return count;
}

void delNode(node **root, int value) {
  if ((*root)->value == value) {
    (*root) = NULL;
    return;
  }
  node *temp = findNode(*root, value);
  if (temp == NULL) {
    printf("There is no node with value %d to delete\n", value);
    return;
  }
  int temp2 = temp->prtNode->value;
  printf("%d\n", temp2);
  temp = temp->prtNode;
  if (temp2 < value) 
    temp->rcNode = NULL;
  else 
    temp->lcNode = NULL;
  // printf("%d\n", temp->value);
}

void inserTree(node *root, int **arr, int *size) {
  if (root == NULL) {
    return;
  } else {
    (*size)++;
    (*arr) = realloc(*arr, (*size)*sizeof(int));
    (*arr)[(*size)-1] = root->value;
  }
  inserTree(root->lcNode, arr, size);
  inserTree(root->rcNode, arr, size);
}

void printSubTree(int value) {
  node *temp = findNode(tree, value);
  if (temp == NULL) {
    printf("There is no node with value %d\n", value);
    return;
  }
  int *newArr = malloc(sizeof(int));
  int size = 0;
  inserTree(temp, &newArr, &size);
  node *subTree = NULL;
  for (int i = 0; i < size; i++) {
    addNode(&subTree, newArr[i]);
  }
  printf("Sub-tree with the root = %d\n", value);
  printTreeVisual(subTree);
}