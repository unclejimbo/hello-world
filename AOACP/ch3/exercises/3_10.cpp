#include <stdio.h>

int main()
{
  FILE *fin = fopen("3_10.in", "r");
  int rec[6][2];
  while(fscanf(fin, "%d %d %d %d %d %d %d %d %d %d %d %d",
	       &rec[0][0], &rec[0][1], &rec[1][0], &rec[1][1],
	       &rec[2][0], &rec[2][1], &rec[3][0], &rec[3][1],
	       &rec[4][0], &rec[4][1], &rec[5][0], &rec[5][1])
	== 12) {
    for (int i = 0; i < 6; ++i) {
      if (rec[i][0] > rec[i][1]) {
	int temp = rec[i][0];
	rec[i][0] = rec[i][1];
	rec[i][1] = temp;
      }
    }
    int flag = 0, k = 0;
    int box[3][2];
    for (int i = 0; i < 6; ++i) {
      for (int j = i + 1; j < 6; ++j) {
	if (rec[i][0] != 0 && rec[j][0] != 0 &&
	    rec[i][0] == rec[j][0] && rec[i][1] == rec[j][1]) {
	  ++flag;
	  box[k][0] = rec[i][0];
	  box[k++][1] = rec[i][1];
	  rec[i][0] = rec[j][0] = 0;
	}
      }
    }
    if (flag != 3) {
      printf("No way!\n");
      continue;
    }
    if ((box[0][0] == box[1][0] && box[0][1] == box[2][1] && box[1][1] == box[2][0]) ||
	(box[0][0] == box[1][1] && box[0][1] == box[2][1] && box[1][0] == box[2][0]) ||
	(box[0][0] == box[1][0] && box[0][1] == box[2][0] && box[1][0] == box[2][1]) ||
	(box[0][0] == box[2][0] && box[0][1] == box[1][1] && box[1][1] == box[2][0]) ||
	(box[0][0] == box[2][1] && box[0][1] == box[1][1] && box[1][0] == box[2][0]) ||
	(box[0][0] == box[2][0] && box[0][1] == box[1][0] && box[1][0] == box[2][1]))
      printf("Bingo!\n");
    else
      printf("No way!\n");
  }
  return 0;
}
