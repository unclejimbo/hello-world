#include <stdio.h>
#include <string.h>
const int MAX_SIZE = 10001;
int ans[MAX_SIZE];

int main()
{
  memset(ans, 0, MAX_SIZE);
  for (int i = 1; i < MAX_SIZE; ++i) {
    int x = i, y = i;
    while (x > 0) {
      y += x % 10;
      x /= 10;
    }
    if(ans[y] == 0 || i < ans[y])
      ans[y] = i;
  }
  int num;
  while (scanf("%d", &num) == 1) {
    printf("%d\n", ans[num]);
  }
  return 0;
}
