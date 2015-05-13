#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  int num[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> numbers(num, num+9);
  while (next_permutation(numbers.begin(), numbers.end())) {
      int a = numbers[0]*100 + numbers[1]*10 + numbers[2];
      int b = numbers[3]*100 + numbers[4]*10 + numbers[5];
      int c = numbers[6]*100 + numbers[7]*10 + numbers[8];
      if (b == a*2 && c == a*3)
	printf("%d %d %d\n", a, b, c);
  }
  return 0;
}
   
