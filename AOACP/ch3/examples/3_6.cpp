#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
  return (*(char*)a - *(char*)b);
}

int main()
{
  //freopen("3_6.in", stdin);
  int len;
  scanf("%d", &len);
  char dna[len][len+1];
  scanf("%s", dna[0]);
  for (int i = 0, j = 0; i < len - 1; ++i) {
    for (int j = 0; j < len; ++j) {
      dna[i+1][j] = dna[i][(j+1)%len];
    }
    dna[i+1][len] = '\0';
    //printf("%s\n", dna[i]);
  }
  int min;
  for (int i = 0; i < len - 1; ++i) {
    if(strncmp(dna[i+1], dna[i], len) < 0)
      min = i + 1;
  }
  printf("%s\n", dna[min]);
  return 0;
}
  
