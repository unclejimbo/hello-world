#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 60000
char str[MAX_SIZE];

void genStr(char *s) {
  for (int i = 1; i <= 10000; ++i) {
    char num[6];
    sprintf(num, "%d", i);
    strncat(s, num, sizeof(num));
    //printf("%d, %d\n", i, strlen(s));
  }
  //printf("success\n");
}
    

int main()
{
  int count[10] = {0};
  genStr(str);
  for (int i = 0; i < strlen(str); ++i) {
    int cur = str[i] - '0';
    ++count[cur];
  }
  for (int i = 0; i < 10; ++i)
    printf("%d, ", count[i]);
  return 0;
}
	   
