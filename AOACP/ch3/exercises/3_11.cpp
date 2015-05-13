#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int MAX_SIZE = 100;

int main()
{
  FILE *fin = fopen("3_11.in", "r");
  char str1[MAX_SIZE], str2[MAX_SIZE];
  while (fscanf(fin, "%s", str1) == 1) {
    fscanf(fin, "%s", str2);
    int len1 = strlen(str1), len2 = strlen(str2);
    int sec1[len1], sec2[len2];
    int minLen = len1 + len2;
    for (int i = 0; i < len1; ++i)
      sec1[i] = str1[i] - '0';
    for (int i = 0; i < len2; ++i)
      sec2[i] = str2[i] - '0'; 
    for (int i = 0; i < len1 + len2; ++i) {
      bool found = false;
      int beg1 = i, beg2 = len1;
      int end1 = i + len1, end2 = len1 + len2;
      int slotLen;
      if (i < len1) 
	end1 < end2 ? slotLen = end2 - beg1 : slotLen = end1 - beg1;
      else
	end1 < end2 ? slotLen = end2 - beg2 : slotLen = end1 - beg2;
      for (int j = 0; j < len1 + len2 + i; ++j) {
	if ((j - beg1 >= 0 && end1 - j > 0) &&
	    (j - beg2 >= 0 && end2 - j > 0)) {
	  if (sec1[j-beg1] + sec2[j-beg2] > 3)
	    break;
	}
	if (j == len1 + len2 + i - 1)
	  found = true;
      }
      if (found && minLen > slotLen)
	minLen = slotLen;
    }
    printf("%d\n", minLen);
  }
  return 0;
}
	
