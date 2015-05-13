#include <stdio.h>
#include <string.h>

int main()
{
  char str[81];
  scanf("%s", str);
  int len = 0;
  bool flag = true;
  for (int i=0, j=1; j < strlen(str); ++j) {
    if (str[i] == str[j] && flag) {
      len = j;
      i = (i + 1) % len;
      flag = !flag;
    } else if (str[i] == str[j] && !flag) {
      i = (i +1) % len;
    } else {
      i = 0;
      len = 0;
      flag = !flag;
    }
  }
  printf("%d\n", len);
  return 0;
}
