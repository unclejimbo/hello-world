#include <stdio.h>
#include <limits.h>
#define MAX_SIZE 100000

int main()
{
  int a, b;
  scanf("%d%d", &a, &b);
  int integer = a / b;
  a = (a % b) * 10;
  int result[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; ++i) {
    result[i] = a / b;
    a = (a % b) * 10;
  }
  int len = 0;
  int i = 1;
  while (i < MAX_SIZE) {
    if (result[i] == result[0]) {
      len = i++;
      int j = 1;
      while (i < MAX_SIZE && result[i] == result[j]) {
	++i; j = (j+1) % len;
      }
      if (i != MAX_SIZE)
	len = 0;
    } else
      ++i;
  }
  if (len != 0) {
    printf("%d.(", integer);
    for (int i = 0; i < len; ++i)
      printf("%d", result[i]);
    printf("), %d\n", len);
  } else {
    printf("Error!");
  }
  return 0;
}
