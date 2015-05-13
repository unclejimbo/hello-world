#include <stdio.h>

int main()
{
  const int price = 95;
  const int bound = 300;
  const double discount = 0.85;
  int count;
  double sum;
  scanf("%d", &count);
  if(price * count > bound)
    sum = price * count * discount;
  else
    sum = price * count;
  printf("%.2f\n", sum);
  return 0;
}
