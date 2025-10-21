#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int value;
  struct node *prtNode;
  struct node *lcNode;
  struct node *rcNode;
} node;

struct ListNode {
    int val;
    struct ListNode *next;
};

// LOT : level of traversal
// VLOT: value in level of traversal
// VsLOT: values in level of traversal

void addNode(node **root, int value);
void delNode(node **root, int value);
//
void printTree(node *root);
void printTreeVisual(node *tree);
//
int maxNode(node *tree);
int numLength(int value);
int count(node *root, int value);
int maxLOT(node *root);
//
void leftCount(node *root, int value, int *count);

// void printTreeShape(node *root, int space);

int main() {
  int arrSize = 0;
  int *arr = NULL;
  arr[arrSize++] = 4;
  arr[arrSize++] = 3;
  arr[arrSize++] = 0;
  arr = realloc(arr, arrSize*sizeof(int));
  for (int i = 0; i < arrSize; i++) {
    printf("[%d]", arr[i]);
  }
  


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

void printTree(node *root) {
  if (root == NULL) {
    return;
  } else {
    // printf("Represent tree in pre-order NLR: ");
    printTree(root->lcNode);
    printf("%d-", root->value);
    printTree(root->rcNode);
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

int numLength(int value) {
  int count = 0;
  while (value > 0) {
    value /= 10;
    count++;
  }
  return count;
}

void leftCount(node *root, int value, int *count) {
  if (root == NULL) {
    return;
  }
  if (root->value <= value) {
    (*count)++;
  }
  // printf("Represent tree in pre-order NLR: ");
  while (root != NULL) {
    if (root->value <= value) {
      (*count)++;
    }
    node *lcNode = root->lcNode;
    node *rcNode = root->rcNode;
    while (lcNode != NULL) {
      if (lcNode->value <= value) {
        (*count)++;
      }
      lcNode;
    }
  }
  leftCount(root->lcNode, value, count);
  leftCount(root->rcNode, value, count);
}

int count(node *root, int value) {
  int count = 0;
  leftCount(root, value, &count);
  return count-1;
}

int maxLOT(node *root) {
  if (root == NULL) {
    return -1;
  }
  int lCount = maxLOT(root->lcNode);
  int rCount = maxLOT(root->rcNode);
  printf("%d-%d\n", lCount, rCount);
  return (lCount > rCount ? lCount : rCount) + 1;
}

void printTreeVisual(node *tree) {
  if (tree == NULL) {
    return;
  }
  // find maxNode
  node *temp = tree;
  int maxNode = temp->value;
  while (temp->rcNode != NULL) {
    temp = temp->rcNode;
  } 
  maxNode = temp->value;
  // find minNode
  temp = tree;
  int minNode = temp->value;
  while (temp->lcNode != NULL) {
    temp = temp->lcNode;
  }
  minNode = temp->value;
  // find max LOT
  int maxLOT = 0, stackSize = 0;
  node **stack = malloc(sizeof(node*));
  

}

char* longestPalindrome1(char* s) {
  int length = 0;
  while (s[length] != '\0') length++;
  //
  char *stack = malloc(length*sizeof(char));
  int sIndex = 0;
  int count = 0, maxSize = 0, index = 0, isFound = 0;
  //
  if (length == 1) {
    return s;
  }
  int back = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    if (back == 0) {
      stack[sIndex++] = s[i];
      back = sIndex;
      isFound = 0;
      if (count > maxSize) {
        maxSize = count;
        index = i - count + 1;
      }
      count = 0;
    } else { /*sIndex >= 1*/
      if (isFound) { // start a valid region
        if (stack[back-1] == s[i]) {
          while (stack[back-1] == s[i+1]) {
            i++;
            count++;
          }
          count += 2;
          if (count > maxSize) {
            maxSize = count;
            index = i - count + 1;
          }
          back--;
        } else {
          if (count > maxSize) {
            maxSize = count;
            index = i - count + 1;
          }
          count = 0;
          isFound = 0;
          stack[sIndex++] = s[i];
          back = sIndex;
        }
      } else { // not found a valid region
        if (stack[back-1] == s[i]) {
          count += 2;
          isFound = 1;
          while (stack[back-1] == s[i+1]) {
            i++;
            count++;
          }
          if (count > maxSize) {
            maxSize = count;
            index = i - count + 1;
          }
          back--;
        } else if (back >= 2 && stack[back-2] == s[i]) {
          count += 3;
          isFound = 1;
          if (count > maxSize) {
            maxSize = count;
            index = i - count + 1;
          }
          back -= 2;
        } else {
          if (count > maxSize) {
            maxSize = count;
            index = i - count + 1;
          }
          count = 0;
          isFound = 0;
          stack[sIndex++] = s[i];
          back = sIndex;
        }
      }
    }
  }
  if (maxSize == 0) {
    char *result = malloc(2*sizeof(char));
    result[0] = s[0];
    result[1] = '\0';
    return result;
  }
  char *result = malloc((maxSize+1)*sizeof(char));
  printf("index : %d\nfirstIndex : %c\nmaxL : %d\n", index, s[index], maxSize);
  for (int i = 0; i < maxSize; i++) {
    result[i] = s[index + i];
  }
  result[maxSize] = '\0';
  return result;
}