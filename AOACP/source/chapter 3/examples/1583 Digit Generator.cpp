#include <iostream>
#include <string>

//#define DRAFT
#ifdef DRAFT
#include <fstream>
#endif

using namespace std;
int main()
{
#ifdef DRAFT
	ifstream in("../../tests/1583.in");
	cin.rdbuf(in.rdbuf());
#endif
	const int MAX = 100000;
	int generators[MAX+100];
	for (int i = 0; i < MAX + 100; ++i)
		generators[i] = i;
	for (int i = 0; i < MAX; ++i) {
		int sum = i, cur = i;
		while ((cur / 10) != 0) {
			sum += cur % 10;
			cur /= 10;
		}
		sum += cur;
		if (generators[sum] > i)
			generators[sum] = i;
	}

	string line;
	getline(cin, line);
	int n = stoi(line);
	for (int i = 0; i < n; ++i) {
		getline(cin, line);
		int num = stoi(line);
		if (generators[num] != num)
			cout << generators[num] << endl;
		else
			cout << 0 << endl;
	}
	return 0;
}