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
	ifstream in("../../tests/1585.in");
	cin.rdbuf(in.rdbuf());
#endif

	string line;
	getline(cin, line);
	int n = stoi(line);
	for (int i = 0; i < n; ++i) {
		getline(cin, line);
		size_t size = line.size();
		int score = 0, beg = -1;
		for (int j = 0; j < size; ++j) {
			if (line[j] == 'O') {
				if (beg == -1)
					beg = j;
				score += j - beg + 1;
			} else {
				beg = -1;
			}
		}
		cout << score << endl;
	}

	return 0;
}