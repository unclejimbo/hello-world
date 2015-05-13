#include <stdio.h>

int main()
{
  int a, b ,c;
  scanf("%d%d%d", &a, &b, &c);
  if (a>=b && a>=c) {
    int d = c;
    c = a;
    a = d;
  } else if (b>=a && b>=c) {
    int d = c;
    c = b;
    b = d;
  }
  if (c >= a + b)
    printf("not a triangle\n");
  if (c * c == a * a + b * b)
    printf("yes\n");
  else
    printf("no\n");
  return 0;
}
