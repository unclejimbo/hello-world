#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1000

int main()
{
  char s[MAX_SIZE], t[MAX_SIZE];
  scanf("%s%s", s, t);
  int len_s = strlen(s);
  //printf("%d\n", len_s);
  int len_t = strlen(t);
  int i_s = 0, i_t = 0;
  while (i_s < len_s && i_t < len_t) {
    if (s[i_s++] == t[i_t])
      ++i_t;
  }
  if (i_t == len_t)
    printf("yes\n");
  else
    printf("no\n");
  return 0;
}
	       
