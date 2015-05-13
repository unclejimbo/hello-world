#include <stdio.h>

int main()
{
  FILE *fin = fopen("3_1.in", "r");
  bool isLeftQuote = true;
  char c;
  while ((c = fgetc(fin)) != EOF) {
    if (c == '\"' && isLeftQuote) {
      printf("``");
      isLeftQuote = !isLeftQuote;
    } else if (c == '\"' && !isLeftQuote) {
      printf("%c", c);
      isLeftQuote = !isLeftQuote;
    } else
      printf("%c", c);
  }
  return 0;
}
    
