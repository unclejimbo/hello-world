#include <stdio.h>
#define cube(x) x*x*x
int main()
{
  for (int i = 100; i < 1000; ++i) {
    int a = i / 100;
    int b = (i / 10) % 10;
    int c = i % 10;
    if (i == cube(a) + cube(b) + cube(c))
      printf("%d ", i);
  }
  return 0;
}
