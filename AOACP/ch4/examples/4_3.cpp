#include <stdio.h>
#include <string.h>

int main()
{
  int n, s1, s2;
  while (scanf("%d %d %d", &n, &s1, &s2) == 3) {
    if (n == 0 && s1 == 0 && s2 == 0)
      break;
    int circle[n];
    int cnt = n;
    int cur1 = 0, cur2 = n - 1;
    for (int i = 0; i < n; ++i)
      circle[i] = 0;
    while (cnt > 0) { 
      int i = s1, j = s2;
      while (i != 0) {
	cur1 = (cur1 + 1) % n;
	if (circle[cur1] == 0) {
	  --i;
	}
      }
      while (j != 0) {
	cur2 - 1 == -1 ? cur2 = n - 1 : cur2 = cur2 - 1;
	if (circle[cur2] == 0) {
	  --j;
	}
      }
      cur1 == cur2 ? cnt -=1 : cnt -= 2;
      circle[cur1] = circle[cur2] = 1;
      printf("%3d%3d,", cur1, cur2);
    }
    printf("\n");
  }
  return 0;
}
