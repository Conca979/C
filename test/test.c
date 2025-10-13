#include <stdlib.h>
#include <stdio.h>

char* longestCommonPrefix(char** strs, int strsSize);

int main() {
  char *strs[] = {"dog","racecar","car"};
  char *prefix = longestCommonPrefix(strs, 3);
  
  for (int i = 0; prefix[i] != '\0'; i++) {
    printf("%c", prefix[i]);
  }
  

  return 0;
}

char* longestCommonPrefix(char** strs, int strsSize) {
  char *prefix = NULL;
  int prefixSize = 0;
  int cont = 1;
  for (int i = 0; cont; i++) {
    char temp = strs[0][i];
    int count = 0;
    if (temp == '\0') break;
    for (int j = 0; j < strsSize; j++) {
      if (strs[j][i] == '\0') {
        cont = 0;
        break;
      } else {
        if (strs[j][i] == temp) {
          count++;
        } else {
          break;
        }
      }
    }
    if (count == strsSize) {
      // printf("-%c\n", temp);
      prefixSize++;
      prefix = realloc(prefix, (prefixSize+1)*sizeof(char));
      prefix[prefixSize] = '\0';
      prefix[prefixSize-1] = temp;
    } else {
      cont = 0;
    }
  }
  if (prefix == NULL) {
    return "";
  } else {
    return prefix;
  }
}