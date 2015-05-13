#include <stdio.h>
#include <string.h>
const char str[] = "`1234567890-=qwertyuiop[]\\asdfghjkl;\'zxcvbnmn./";

int main()
{
  char c;
  while ((c = getchar()) != 'a') {
    char *p = strchr(str, c);
    printf("%c", *(--p));
  }
  return 0;
}
