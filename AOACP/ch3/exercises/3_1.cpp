#include <stdio.h>
#include <string.h>
#define MAX_SIZE 81

int main()
{
  char s[MAX_SIZE];
  scanf("%s", s);
  int flag = 0, score = 0, conseqution = 0;
  for (int i = 0; i < strlen(s); ++i) {
    if (s[i] == 'O') {
      if (flag) 
	score += ++conseqution;
      else {
	score += ++conseqution;
	flag = 1;
      }
    } else {
      if (flag) {
	flag = 0;
	conseqution = 0;
      }
    }
  }
  printf("%d\n", score);
  return 0;
}
