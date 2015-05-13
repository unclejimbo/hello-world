#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

int main()
{
  char puzzle[5][5];
  char p_str[26];
  char inst[MAX_SIZE];
  int x, y;
  FILE *fin = fopen("3_5.in", "r");
  fgets(p_str, sizeof(p_str), fin);
  printf("String:%s\n", p_str);
  printf("Original puzzle:\n");  
  for (int i = 0, k = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      puzzle[i][j] = p_str[k++];
      printf("%c ", puzzle[i][j]);
      if (puzzle[i][j] == ' ') {
	x = i; y = j;
      }
    }
    printf("\n");
  }
  scanf("%s", inst);
  for (int i = 0; i < strlen(inst); ++i) {
    switch (inst[i]) {
    case 'L':
      if (y == 0) {
	printf("Illegal instruction.");
        return 0;
      }
      puzzle[x][y] = puzzle[x][y-1];
      puzzle[x][--y] = ' ';
      break;
    case 'R' :
      if (y == 5) {
	printf("Illegal instruction.");
        return 0;
      }
      puzzle[x][y] = puzzle[x][y+1];
      puzzle[x][++y] = ' ';
      break;
    case 'A' :
      if (x == 0) {
	printf("Illegal instruction.");
        return 0;
      }
      puzzle[x][y] = puzzle[x-1][y];
      puzzle[--x][y] = ' ';
      break;
    case 'B' :
      if (x == 5) {
	printf("Illegal instruction.");
        return 0;
      }
      puzzle[x][y] = puzzle[x+1][y];
      puzzle[++x][y] = ' ';
      break;
    }
  }
  printf("Final puzzle:\n");  
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      printf("%c ", puzzle[i][j]);
    }
    printf("\n");
  }
  return 0;
}
      
