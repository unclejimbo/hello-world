#include <stdio.h>
#include <string.h>
const int MAXN = 20;

int main()
{
  FILE *fin = fopen("4_2.in", "r");
  int round;
  fscanf(fin, "%d", &round);
  while (round != -1) {
    printf("Ronund %d\n", round);
    char answer[MAXN], guess[MAXN];
    fscanf(fin, "%s", answer);
    fscanf(fin, "%s", guess);
    int cnt[26] = {0};
    int wrong = 0, num = 0;
    for (int i = 0; i < strlen(answer); ++i) {
      int pos = answer[i] - 'a';
      if (cnt[pos] == 0) {
	cnt[pos] = 1;
	++num;
      }
    }
    for (int i = 0; i < strlen(guess); ++i) {
      int pos = guess[i] - 'a';
      if (cnt[pos] == 1) {
	cnt[pos] = 0;
	--num;
      }
      else
	++wrong;
    }
    if (num == 0)
      printf("You win.\n");
    else {
      if (wrong <7)
	printf("You chickened out.\n");
      else
	printf("You lose.\n");
    }
    fscanf(fin, "%d", &round);
  }
  return 0;
}
