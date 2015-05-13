#include <stdio.h>
#include <math.h>

int main()
{
  const double pi = acos(-1.0);
  int d;
  scanf("%d", &d);
  printf("%f\n", sin(d*pi/180));
  return 0;
}
