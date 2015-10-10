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
	ifstream in("../../tests/1225.in");
	cin.rdbuf(in.rdbuf());
#endif

	string line;
	getline(cin, line);
	int n = stoi(line);
	while (n--) {
		getline(cin, line);
		int len = stoi(line);
		int count[10] = { 0 };
		while (len) {
			int cur = len--;
			while (cur / 10 != 0) {
				++count[cur % 10];
				cur /= 10;
			}
			++count[cur];
		}
		for (int i = 0; i < 9; ++i) {
			cout << count[i] << " ";
		}
		cout << count[9] << endl;
	}

	return 0;
}