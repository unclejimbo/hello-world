#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
  int m, n;
  scanf("%d%d", &m, &n);
  char dna[m][n+2];
  FILE *fin = fopen("3_7.in", "r");
  for (int i = 0; i < m; ++i) 
    fgets(dna[i], sizeof(dna[i]), fin);
  #ifdef DEBUG
  for (int i = 0; i < m; ++i)
    printf("%s", dna[i]);
  #endif
  int count[n][4];
  for (int i = 0; i < n; ++i) 
    memset(count[i], 0, sizeof(count[i]));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      switch (dna[i][j]) {
      case 'T': count[j][0]++; break;
      case 'A': count[j][1]++; break;
      case 'C': count[j][2]++; break;
      case 'G': count[j][3]++; break;
      default : ;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    int max = -1;
    char name;
    for (int j = 0; j < 4; ++j) {
      if (max < count[i][j]) {
	max = count[i][j];
	switch (j) {
	case 0 : name = 'T'; break;
	case 1 : name = 'A'; break;
	case 2 : name = 'C'; break;
	case 3 : name = 'G'; break;
	default: ;
	}
      }
    }
    printf("%c", name);
  }
  printf("\n");
  return 0;
}
