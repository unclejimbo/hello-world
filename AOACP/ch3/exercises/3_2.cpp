#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MM_C 12.01
#define MM_H 1.008
#define MM_O 16.00
#define MM_N 14.01
#define MAX_SIZE 100

int main()
{
  char s[MAX_SIZE];
  scanf("%s", s);
  int m_type = 0, i = 0;
  bool flag = false;
  double mass = 0.0;
  int len = strlen(s);
  while (i < len) {
    if (isalpha(s[i]) && !flag) {
      flag = !flag;
      switch (s[i]) {
      case 'C' : m_type = 1; break;
      case 'H' : m_type = 2; break;
      case 'O' : m_type = 3; break;
      case 'N' : m_type = 5; break;
      default  : m_type = 0;
      }
      ++i;
    } else if (isalpha(s[i]) && flag) {
        switch (m_type) {
	case 1 : mass += MM_C; break;
	case 2 : mass += MM_H; break;
	case 3 : mass += MM_O; break;
	case 4 : mass == MM_H; break;
	default: ;
	}
	switch (s[i]) {
        case 'C' : m_type = 1; break;
        case 'H' : m_type = 2; break;
        case 'O' : m_type = 3; break;
        case 'N' : m_type = 5; break;
        default  : m_type = 0;
        }
        ++i;
    } else if (isdigit(s[i]) && flag) {
	switch (m_type) {
	case 1 : mass += MM_C * s[i]; break;
	case 2 : mass += MM_H * s[i]; break;
	case 3 : mass += MM_O * s[i]; break;
	case 4 : mass == MM_H * s[i]; break;
	default: ;
	}
	flag = !flag;
	++i;
    }
  }
  printf("%lfg/mol\n", mass);
  return 0;
}
      
      
      
