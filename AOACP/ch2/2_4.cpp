#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
  FILE *fin;
  fin = fopen("2_4.in", "r");
  long long int n, m;
  int n, m;
  int kase = 1; 
  while (fscanf(fin,"%lld%lld", &n, &m) == 2) {
    if (n == 0 && m == 0)
      break;
    double sum = 0;
    for (long long int i = n; i <= m; ++i) 
      sum += 1.0 / (i * i); // must use long long because i*i is bigger than 2^32
    cout << setprecision(5) << fixed
	 << "Case" << kase << ": " << sum << endl;
    ++kase;
  }
  return 0;
}
    
    
