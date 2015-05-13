#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
const int MAXN = 50;
const double EPS = 0.0001;

const int E[MAXN] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215, 33554431, 67108863, 134217727, 268435455, 536870911, 1073741823};  
  
const double M[MAXN] = {0.500000000000000, 0.750000000000000, 0.875000000000000, 0.937500000000000, 0.968750000000000, 0.984375000000000, 0.992187500000000, 0.996093750000000, 0.998046875000000, 0.999023437500000, 0.999511718750000};

int main()
{
  char str[MAXN];
  FILE *fin = fopen("3_12.in", "r");
  fscanf(fin, "%s", str);
  while (strcmp(str, "0e0") != 0) {
    int i = 0, len = strlen(str);
    while (str[i++] != 'e')
      ;
    char mPart[i], ePart[len - i];
    strncpy(mPart, str, i - 1);
    mPart[i-1] = '\0';
    strncpy(ePart, str + i*sizeof(char), len - i + 1);
    double m = atof(mPart);
    int e = atoi(ePart);
    double result = log10(m) + e;
    for (int i = 0; i <= 9; ++i) {
      for (int j = 1; j <= 30; ++j) {
	if (fabs((log10(M[i]) + E[j] * log10(2)) - result) < EPS)
	  printf("%d %d\n", i, j);
      }
    }
    fscanf(fin, "%s", str);
  }
  return 0;
}
