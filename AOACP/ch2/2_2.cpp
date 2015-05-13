#include <stdio.h>

int main()
{
  FILE *fin;
  fin = fopen("2_2.in", "rb");
  int a, b, c, kase = 0;
  while(fscanf(fin, "%d%d%d", &a, &b, &c) == 3) {
    int flag = 1;
    for (int i = 10; i <= 100; ++i) {
      if (i%3 == a && i%5 == b && i%7 == c) {
        printf("Case %d: %d\n", kase, i);
	flag = 0;
	break;
      }
    }
    if (flag)
      printf("Case %d: No answer\n", kase);
    ++kase;
  }
  fclose(fin);
  return 0;
}
