#include <stdio.h>
#include <string.h>

int main()
{
  FILE *fin = fopen("3_4.in", "r");
  int num, round = 1;
  while (fscanf(fin, "%d", &num) == 1 && num != 0) {
    printf("Game %d:\n", round++);
    char answer[num+1];
    fscanf(fin, "%s", answer);
    char attemp[num+1];
    char termination[num+1];
    memset(termination, '0', num);
    termination[num] = '\0';
    while (fscanf(fin, "%s", attemp) == 1 && strcmp(termination, attemp)) {
      int posRight = 0, posWrong = 0;
      char tempAns[num], tempAtt[num];
      int k = 0;
      for (int i = 0; i < num; ++i) {
	if (attemp[i] == answer[i]) 
	  ++posRight;
	else {
	  tempAns[k] = answer[i];
	  tempAtt[k++] = attemp[i];
	}
      }
      for (int i = 0; i < num - posRight; ++i) {
	for (int j = 0; j < num - posRight; ++j) {
	  if (tempAns[j] == tempAtt[i] && tempAns[j] != ' ') {
	    ++posWrong;
	    tempAns[j] = ' ';
	    break;
	  }
	}
      }
      printf("(%d,%d)\n", posRight, posWrong);
    }
  }
  return 0;
}
	  
