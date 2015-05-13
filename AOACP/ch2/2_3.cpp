#include <stdio.h>

int main()
{
  int n;
  scanf("%d", &n);
  int count = 2 * n - 1;
  for (int i = n; i > 0; --i) {
    int sharpes = 2 * i - 1;
    int spaces1 = (count - sharpes) / 2;
    int spaces2 = spaces1;
    while(spaces1-- > 0)
      printf(" ");
    while(sharpes-- > 0)
      printf("#");
    while(spaces2-- > 0)
      printf(" ");
    printf("\n");
  }
  return 0;
}
