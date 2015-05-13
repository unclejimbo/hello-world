#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
  FILE *fin = fopen("2_5.in", "r");
  int a, b ,c;
  while (fscanf(fin, "%d%d%d", &a, &b, &c) == 3) {
    if (a == 0 && b == 0 && c == 0)
      break;
    double result = double(a) / double(b);
    cout << setprecision(c) << fixed
	 << result << endl;
  }
  return 0;
}
