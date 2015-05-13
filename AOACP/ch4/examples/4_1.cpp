#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAXN = 101;

int cmp(const void *p1, const void *p2) {
  if (*(int*)p1 > *(int*)p2) return 1;
  else if (*(int*)p1 == *(int*)p2) return 0;
  else return -1;
}


int main()
{
  FILE *fin = fopen("4_1.in", "r");
  char encrypt[MAXN], msg[MAXN];
  while (fscanf(fin, "%s%s", encrypt, msg) == 2) {
    int len = strlen(msg);
    int eCount[26] = {0};
    int mCount[26] = {0};
    for (int i = 0; i < len; ++i) {
      ++eCount[encrypt[i] - 'A'];
      ++mCount[msg[i] - 'A'];
    }
    qsort(eCount, 26, sizeof(int), cmp);
    qsort(mCount, 26, sizeof(int), cmp);
    int ok = 1;
    for (int i = 0; i < 26; ++i) {
      if (eCount[i] != mCount[i]) 
        ok = 0;
    }
    if (ok)
      printf("Yes\n");
    else
      printf("No\n");
  }
  return 0;
}
