#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 101

int main()
{
  FILE *fin = fopen("3_6.in", "r");
  char str[MAX_SIZE];
  fgets(str, MAX_SIZE, fin);
  int round = 1;
  while (str[0] != '0') {
    int r = str[0] - '0', c = str[2] - '0';
    char crossword[r][c];
    int eligible[r][c];
    fgets(str, MAX_SIZE, fin);
    for (int i = 0, k = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
	crossword[i][j] = str[k++];
      }
    }
    for (int i = 0, k = 1; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
	if ((i == 0 || j == 0) &&
	    (crossword[i][j] != '*'))
	  eligible[i][j] = k++;
	else if ((crossword[i][j-1] == '*' ||
		  crossword[i-1][j] == '*') &&
		 crossword[i][j] != '*')
	  eligible[i][j] = k++;
	else
	  eligible[i][j] = 0;
      }
    }
    printf("Puzzle #%d:\n", round++);
    printf("Across ");
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
	if (eligible[i][j] != 0 &&
	    (j == 0 || crossword[i][j-1] == '*')) {
	  printf("%d.", eligible[i][j]);
	  int cur = j;
	  while (cur < c && crossword[i][cur] != '*')
	    printf("%c", crossword[i][cur++]);
	  printf(" ");
	}
      }
    }
    printf("Down ");
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
	if (eligible[i][j] != 0 &&
	    (i == 0 || crossword[i-1][j] == '*')) {
	  printf("%d.", eligible[i][j]);
	  int cur = i;
	  while (cur < r && crossword[cur][j] != '*')
	    printf("%c", crossword[cur++][j]);
	  printf(" ");
	}
      }
    }
    printf("\n");
    fgets(str, MAX_SIZE, fin);
  }
  return 0;
}
		 
    
