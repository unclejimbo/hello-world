#include <stdio.h>
#include <string.h>
#include <ctype.h>
const char rev[] = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char* msg[] = {"is not a plindrome", "is a regular palindrome",
		     "is a mirrored string", "is a mirrored palindrome"};
const int MAX_SIZE = 100;

int main()
{
  FILE *fin = fopen("3_3.in", "r");
  char s[MAX_SIZE];
  while(fscanf(fin, "%s", s) == 1) {
    int len = strlen(s);
    int isP = 1, isM = 1;
    for (int i = 0; i < (len+1)/2; ++i) {
      if (s[i] != s[len-i-1]) {
	isP = 0;
	break;
      }
    }
    for (int i = 0; i < (len+1)/2; ++i) {
      int pos;
      if (isdigit(s[i]))
	pos = 26 + s[i] - '1';
      else
	pos = s[i] - 'A';
      if (rev[pos] == ' ') {
	isM = 0;
	break;
      }
    }
    printf("%s--%s\n", s, msg[isP+(isM<<1)]);
  }
  return 0;
}
