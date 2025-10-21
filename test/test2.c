#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

bool isPalindrome(int x);
int* twoSum(int* nums, int numsSize, int target, int* returnSize);
bool exist(char** board, int boardSize, int* boardColSize, char* word);
char* intToRoman(int num);
int removeDuplicates(int* nums, int numsSize);
int removeElement(int* nums, int numsSize, int val);
int strStr(char* haystack, char* needle);
int searchInsert(int* nums, int numsSize, int target);
int lengthOfLastWord(char* s);
int romanToInt(char* s);
int romanToInt2(char* s);
int maxArea(int* height, int heightSize);
bool isValid(char* s);
int* plusOne(int* digits, int digitsSize, int* returnSize);
char* addBinary(char* a, char* b);
void mergeSort(int *arr, int arrSize);
int longestValidParentheses(char* s);
char* longestPalindrome1(char* s);
int pairSimilarity(char *w1, char *w2);
int longestSimilarity(char **aos, int nums);

int main() {
  char *String[] = {"", "a", "aa", "aabbcbbaa", "abccdbdcc"};
  for (int i = 0; i < sizeof(String)/sizeof(*String); i++) {
    printf("\"%s\" = \"%s\"\n", String[i], longestPalindrome1(String[i]));
  }
  //
  // char test[] = "racecar";
  // printf("\"%s\" = \"%s\"\n", test, longestPalindrome1(test));

  return 0;
}

int* plusOne(int* digits, int digitsSize, int* returnSize) {
  int carry = 0;
  int *revered = malloc(digitsSize*sizeof(int));
  for (int i = 0; i < digitsSize; i++) {
    revered[i] = digits[digitsSize-1-i];
  }
  int first = revered[0] + 1;
  if (first >= 10) {
    carry = 1;
    revered[0] = 0;
  } else {
    (*returnSize) = digitsSize;
    int *result = malloc(digitsSize*sizeof(int));
    for (int i = 0; i < digitsSize; i++) {
      result[i] = digits[i];
    }
    result[digitsSize - 1] += 1;
    return result;
  }
  //
  for (int i = 1; i < digitsSize && carry != 0; i++) {
    if (revered[i] + carry >= 10) {
      revered[i] = 0;
      carry = 1;
    } else {
      revered[i] += carry;
      carry = 0;
    }
  }
  if (carry == 1) {
    digitsSize++;
    (*returnSize) = digitsSize;
    revered = realloc(revered, digitsSize*sizeof(int));
    revered[digitsSize-1] = 1;
    int *result = malloc(digitsSize*sizeof(int));
    for (int i = 0; i < digitsSize; i++) {
      result[i] = revered[digitsSize-1-i];
    }
    return result;
  } else {
    (*returnSize) = digitsSize;
    int *result = malloc(digitsSize*sizeof(int));
    for (int i = 0; i < digitsSize; i++) {
      result[i] = revered[digitsSize-1-i];
    }
    return result;
  }
}

bool isPalindrome(int x) {
  if (x < 0) {
      return false;
  } else {
      int size = 0, temp = x;
      while (temp != 0) {
          size++;
          temp = temp/10;
      }
      int new = 0;
      temp = x;
      for (int i = 0; i < size; i++) {
          new = new*10 + temp%10;
          printf("-%d-\n", new);
          temp /= 10;
      }
      if (new == x) {
          return true;
      } else {
          return false;
      }
  }
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  int *indices = malloc(2*sizeof(int));
  for (int i = 0; i < numsSize-1; i++) {
    for (int j = i+1; j < numsSize; j++) {
      if ((nums[i]+nums[j]) == target) {
        indices[0] = i;
        indices[1] = j;
        (*returnSize) = 2;
        return indices;
      }
    }
  }
}

char* intToRoman(int num) {
  int romanSize = 1;
  char *roman = malloc(sizeof(char));
  roman[0] = '\0';
  int numSize = 0, temp = num;
  while (temp != 0) {
    numSize++;
    temp /= 10;
  }
  char symbol[] = "IVXLCDM";
  char powOf10[] = "IXCMVLD";
  for (int i = 0; i < numSize; i++) {
    int token = num%10;
    if (token < 4) {
      int newSize = romanSize + token;
      roman = realloc(roman, newSize*sizeof(int));
      for (int j = romanSize; j < newSize; j++) {
        romanSize++;
        roman[j] = '\0';
        roman[j-1] = symbol[i*2];
      }
    } else if (token >= 5 && token < 9) {
      int newSize = romanSize + token - 4;
      roman = realloc(roman, newSize*sizeof(int));
      for (int j = romanSize; j < newSize-1; j++) {
        romanSize++;
        roman[j] = '\0';
        roman[j-1] = symbol[i*2];
      }
      roman[romanSize-1] = powOf10[i+4];
      roman[romanSize] = '\0';
      romanSize++;
    } else { // when toekn = 4 or 9
      int newSize = romanSize + 2;
      romanSize += 2;
      roman = realloc(roman, newSize*sizeof(int));
      roman[newSize-1] = '\0';
      roman[newSize-2] = powOf10[i];
      roman[newSize-3] = powOf10[i+(token==4?4:1)];
    }
    num /= 10;
  }
  for (int i = 0; i < (romanSize-1)/2; i++) {
    int temp = roman[i];
    roman[i] = roman[romanSize-2-i];
    roman[romanSize-2-i] = temp;
  }
  return roman;
}

int removeDuplicates(int* nums, int numsSize) {
  int *unique = malloc(numsSize*sizeof(int));
  int uniqueCount = 0;
  for (int i = 0; i < numsSize; i++) {
    if (uniqueCount != 0) {
      int token = unique[uniqueCount-1];
      if (token < nums[i]) {
        uniqueCount++;
        unique[uniqueCount-1] = nums[i];
      }
    } else {
      uniqueCount++;
      unique[uniqueCount-1] = nums[0];
    }
  }
  //
  for (int i = 0; i < uniqueCount; i++) {
    nums[i] = unique[i];
  }
  //
  return uniqueCount;
}

int removeElement(int* nums, int numsSize, int val) {
  int *new = malloc(numsSize*sizeof(int));
  int k = 0;
  for (int i = 0; i < numsSize; i++) {
    if (nums[i] != val) {
      new[k] = nums[i];
      k++;
    }
  }
  for (int i = 0; i < k; i++) {
    nums[i] = new[i];
  }
  return k;
}

int strStr(char* haystack, char* needle) {
  int hsSize = 0, nSize = 0;
  for (int i = 0; haystack[i] != '\0'; i++) {
    hsSize++;
  }
  for (int i = 0; needle[i] != '\0'; i++) {
    nSize++;
  }
  for (int i = 0; i < hsSize; i++) {
    if (haystack[i] == needle[0]) {
      int count = 0;
      for (int j = i, h = 0; (j < hsSize) && (h < nSize); j++, h++) {
        if (haystack[j] == needle[h]) {
          count++;
        } else break;
      }
      if (count == nSize) {
        return i;
      }
    }
  }
  return -1;
}

int searchInsert(int* nums, int numsSize, int target) {
  if (nums[numsSize-1] == target) return numsSize-1; 
  else if (nums[numsSize-1] < target) return numsSize;
  else if (nums[0] >= target) return 0;
  int index = numsSize/2, bound = numsSize-1;
  while ((bound-index) > 1) {
    if (target < nums[index]) {
      bound = index;
      index /= 2;
    } else if (target > nums[index]) {
      index = (index+bound)/2;
    } else return index;
  }
  return bound;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
  if (head == NULL) {
    return NULL;
  } else {
    struct ListNode *nodes = malloc(sizeof(struct ListNode));
    nodes->val = head->val;
    nodes->next = NULL;
    head = head->next;
    struct ListNode *temp = nodes;
    while (head != NULL) {
      if (temp->val != head->val) {
        temp->next = malloc(sizeof(struct ListNode));
        temp->next->val = head->val;
        temp->next->next = NULL;
        temp = temp->next;
      }
      head = head->next;
    }
    return nodes;
  }
}

int lengthOfLastWord(char* s) {

  int sSize = 0, lwSize = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    sSize++;
  }
  for (int i = sSize-1; i >= 0; i--) {
    if (s[i] != ' ') {
      for (int j = i; j >= 0 && s[j] != ' '; j--) {
        lwSize++;
      }
      break;
    }
  }
  return lwSize;
}

int romanToInt(char* s) {
  char symbols[] = "IVXLCDM";
  int values[] = {1, 5, 10, 50, 100, 500, 1000};
  int number = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    int index = 0;
    for (int j = 0; j <= 6; j++) {
      if (symbols[j] == s[i]) {
        index = j;
        break;
      }
    }
    printf("[%d, [%c|%c]]\n", index, s[i], s[i+1]);
    if (index <= 5 && (s[i+1] != '\0')) {
      if (index <= 4) {
        if (s[i+1] == symbols[index+2]) {
          number += (values[index+2] - values[index]);
          i++;
          continue;
        }
      }
      if (s[i+1] == symbols[index+1]) {
        number += (values[index+1] - values[index]);
        i++;
        continue;
      } else {
        number += values[index];
        continue;
      }
    } else {
      number += values[index];
      continue;
    }
  }
  return number;
}

int romanToInt2(char* s) {
  char symbols[] = "IVXLCDM";
  int values[] = {1, 5, 10, 50, 100, 500, 1000};
  int number = 0, sSize = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    sSize++;
  }
  int rIndex = 0;
  for (int i = sSize-1; i >= 0; i--) {
    int index = 0;
    for (int j = 0; j < 7; j++) {
      if (s[i] == symbols[j]) {
        index = j; break;
      }
    }
    if (index < rIndex) {
      number -= values[index];
      rIndex = index;
    } else {
      number += values[index];
      rIndex = index;
    }
  }
  return number;
}

int maxArea(int* height, int heightSize) {
  int area = 0, lIndex = 0, rIndex = heightSize-1;
  while (lIndex < rIndex) {
    int newArea = (rIndex - lIndex)*(height[lIndex]>height[rIndex]?height[rIndex]:height[lIndex]);
    area = area < newArea ? newArea : area;
    if (height[lIndex] < height[rIndex]) {
      lIndex++;
    } else {
      rIndex--;
    }
  }
  return area;
}

// [705634720]

bool isValid(char* s) {
  int stackSize = 0;
  char *stack = malloc(strlen(s));
  char parents[] = "({[)}]";
  for (int i = 0; s[i] != '\0'; i++) {
    int index = 0;
    for (int j = 0; j <= 5; j++) {
      if (s[i] == parents[j]) {
        index = j;
        break;
      }
    }
    if (index <= 2) {
      stackSize++;
      stack[stackSize-1] = s[i];
    } else {
      if (stackSize == 0) {
        return false;
      } else {
        if (parents[index-3] == stack[stackSize-1]) {
          stackSize--;
        } else {
          return false;
        }
      }
    }
  }
  if (stackSize == 0) return true;
  else return false;
}

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
  struct ListNode merge;
  struct ListNode *temp = &merge;
  temp->next = NULL;
  while (list1 != NULL && list2 != NULL) {
    struct ListNode *new = malloc(sizeof(struct ListNode));
    if (list1->val > list2->val) {
      new->val = list2->val;
      new->next = NULL;
      //
      temp->next = new;
      temp = temp->next;
      list2 = list2->next;
    } else {
      new->val = list1->val;
      new->next = NULL;
      //
      temp->next = new;
      temp = temp->next;
      list1 = list1->next;
    }
  }
  while (list1 != NULL) {
    struct ListNode *new = malloc(sizeof(struct ListNode));
    new->val = list1->val;
    new->next = NULL;
    //
    temp->next = new;
    temp = temp->next;
    list1 = list1->next;
  }
  while (list2 != NULL) {
    struct ListNode *new = malloc(sizeof(struct ListNode));
    new->val = list2->val;
    new->next = NULL;
    //
    temp->next = new;
    temp = temp->next;
    list2 = list2->next;
  }
  return merge.next;
}

char* addBinary(char* a, char* b) {
  int aSize = 0, bSize = 0;
  for (int i = 0; a[i] != '\0'; i++) {
    aSize++;
  }
  for (int i = 0; b[i] != '\0'; i++) {
    bSize++;
  }
  printf("[%d|%d]\n", aSize, bSize);
  int carry = 0, sumIndex = aSize>bSize?aSize:bSize, sumSize = sumIndex + 1;
  char *sum = malloc(sumSize*sizeof(char));
  sum[sumIndex--] = '\0';
  while (aSize > 0 && bSize > 0) {
    if (a[aSize-1] - '0' + b[bSize-1] - '0' + carry >= 2) {
      sum[sumIndex--] = (char) ((a[aSize-1] - '0' + b[bSize-1] - '0' + carry)%2 + 48);
      carry = 1;
      aSize--;
      bSize--;
    } else {
      sum[sumIndex--] = (char) (a[aSize-1] - '0' + b[bSize-1] - '0' + carry + 48);
      carry = 0;
      aSize--;
      bSize--;
    }
  }
  while (aSize > 0) {
    if (a[aSize-1] - '0' + carry >= 2) {
      sum[sumIndex--] = (char) ((a[aSize-1] - '0' + carry)%2 + 48);
      carry = 1;
      aSize--;
    } else {
      sum[sumIndex--] = (char) (a[aSize-1] - '0' + carry + 48);
      carry = 0;
      aSize--;
    }
  }
  while (bSize > 0) {
    if (b[bSize-1] - '0' + carry >= 2) {
      sum[sumIndex--] = (char) ((b[bSize-1] - '0' + carry)%2 + 48);
      carry = 1;
      bSize--;
    } else {
      sum[sumIndex--] = (char) (b[bSize-1] - '0' + carry + 48);
      carry = 0;
      bSize--;
    }
  }
  if (carry != 0) {
    char *new = malloc((++sumSize)*sizeof(char));
    for (int i = 0; i < sumSize - 1; i++) {
      new[i+1] = sum[i];
    }
    new[0] = '1';
    printf("{result size = %d}\n", sumSize);
    return new;
  } else {
    printf("{result size = %d}\n", sumSize);
    return sum;
  }
}

void mergeSort(int *arr, int arrSize) {
  if (arrSize < 2) return;
  int leftSize = arrSize/2;
  int rightSize = arrSize - leftSize;
  //
  // spliting 
  int leftArr[leftSize];
  for (int i = 0; i < leftSize; i++) {
    leftArr[i] = arr[i];
  }
  int rightArr[rightSize];
  for (int i = 0; i < rightSize; i++) {
    rightArr[i] = arr[leftSize+i];
  }
  //
  if (leftSize > 1) {
    mergeSort(leftArr, leftSize);
  }
  if (rightSize > 1) {
    mergeSort(rightArr, rightSize);
  }
  //
  //sort
  int leftIndex = 0, rightIndex = 0, arrIndex = 0;
  while ((leftIndex < leftSize) && (rightIndex < rightSize)) {
    if (leftArr[leftIndex] <= rightArr[rightIndex]) {
      arr[arrIndex] = leftArr[leftIndex];
      leftIndex++;
      arrIndex++;
    } else {
      arr[arrIndex] = rightArr[rightIndex];
      rightIndex++;
      arrIndex++;
    }
  }
  for (int i = 0; leftIndex < leftSize; i++) {
    arr[arrIndex+i] = leftArr[leftIndex];
    leftIndex++;
  }
  for (int i = 0; rightIndex < rightSize; i++) {
    arr[arrIndex+i] = rightArr[rightIndex];
    rightIndex++;
  }
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  int size = 0;
  for (int i = 0; i < listsSize; i++) {
    struct ListNode *temp = lists[i];
    while (temp != NULL) {
      size++;
      temp = temp->next;
    }
  }
  int *arr = malloc(size*sizeof(int));
  int index = 0;
  for (int i = 0; i < listsSize; i++) {
    struct ListNode *temp = lists[i];
    while (temp != NULL) {
      arr[index++] = temp->val;
      temp = temp->next;
    }
  }
  mergeSort(arr, size);
  //
  struct ListNode dummy;
  struct ListNode *temp = &dummy;
  temp->next = NULL;
  for (int i = 0; i < size; i++) {
    struct ListNode *new = malloc(sizeof(struct ListNode));
    new->val = arr[i];
    new->next = NULL;
    temp->next = new;
    temp = temp->next;
  }
  return dummy.next;
}


// ")()((())"
// "))))))()"
// "()(())"
// ")(())
// "(()())"
int longestValidParentheses(char* s) // not completed yet
 {
  int maxCount = 0, count = 0, size = 0, sSize = 0;
  int maxCount2 = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    size++;
  }
  // 
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] == ')') {
      if (sSize == 0) {
        maxCount = maxCount>count?maxCount:count;
        count = 0;
      } else {
        count += 2;
        sSize--;
      }
    } else {
      sSize++;
    }
  }
  //
  sSize = 0, count = 0;
  char *revered = malloc((size+1)*sizeof(char));
  revered[size] = '\0';
  for (int i = 0; i < size; i++) {
    revered[i] = s[size-1-i];
  }
  for (int i = 0; s[i] != '\0'; i++) {
    if (revered[i] == '(') {
      if (sSize == 0) {
        maxCount2 = maxCount2>count?maxCount2:count;
        count = 0;
      } else {
        count += 2;
        sSize--;
      }
    } else {
      sSize++;
    }
  }
  //
  return maxCount2>maxCount?maxCount2:maxCount;
}

int pairSimilarity(char *w1, char *w2) {
  int maxS = 0, s = 0;
  //
  for (int i = 0; w1[i] != '\0'; i++) {
    for (int j = 0; w2[j] != '\0'; j++) {
      if (w2[j] == w1[i]) {
        for (int k = 0; w1[i+k] != '\0' && w2[j+k] != '\0' && w1[i+k] == w2[j+k]; k++) {
          s++;
        }
        maxS = maxS>s?maxS:s;
        s = 0;
      }
    }
  }
  //
  return maxS;
}

char* longestPalindrome1(char* s) {
  int n = strlen(s);
  if (n == 0) return "";
  int start = 0, maxLen = 1;
  
  for (int center = 0; center < n; center++) {
    int l = center, r = center;
  }
  //
  int maxS = 0, back = 0, index = 0;
  int count = 0, isFound = 0, backWalk = 0;
  if (n == 1) return s;
  int len = strlen(s);
  for (int i = 0; s[i] != '\0'; i++) {
    if (!isFound) {
      // printf("[%d]\n", i);
      i = i - backWalk + 1;
      back = i, backWalk = 0;
    }
    if (back < 0) back = 0;
    if (back == 0) { // back == 0
      if (count > maxS) {
        maxS = count;
        index = back;
      }
      isFound = 0;
      backWalk = count;
      count = 0;
    } else { // back >= 1
      if (isFound) { // in valid region
        if (s[i] == s[back-1]) {
          count += 2, back--;
          if (count > maxS) {
            maxS = count;
            index = back;
          }
        } else {
          if (count > maxS) {
            maxS = count;
            index = back;
          }
          backWalk = count;
          isFound = 0, count = 0;
        }
      } else { // finding symmetric
        if (s[i] == s[back-1]) {
          count += 2, back--, isFound = 1;
          while (s[i] == s[i+1]) {
            i++, count++;
          }
          if (count > maxS) {
            maxS = count;
            index = back;
          }
        } else if (back >= 2) {
          if (s[i] == s[back-2]) {
            count += 3, back -= 2, isFound = 1;
            if (count > maxS) {
              maxS = count;
              index = back;
            }
          } 
        } else {
          if (count > maxS) {
            maxS = count;
            index = back;
          }
          backWalk = count;
          count = 0;
        }
      }
    }
  }
  //
  if (maxS == 0) { 
    maxS = 1; 
    index = 0; 
  }
  char *result = malloc((maxS+1)*sizeof(char));
  for (int i = 0; i < maxS; i++) {
    result[i] = s[index+i];
  }
  result[maxS] = '\0';
  printf("[index : %d |maxS : %d]\n", index, maxS);
  return result;
}