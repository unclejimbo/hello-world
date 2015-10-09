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
	ifstream in("../../tests/1584.in");
	cin.rdbuf(in.rdbuf());
#endif

	string line;
	getline(cin, line);
	int n = stoi(line);
	for (int i = 0; i < n; ++i) {
		getline(cin, line);
		string ans = line;
		size_t size = line.size();
		for (int i = 1; i < size; ++i) {
			string sub1 = line.substr(i, size - i);
			string sub2 = line.substr(0, i);
			sub1.append(sub2);
			if (sub1 < ans)
				ans = sub1;
		}
		cout << ans << endl;
	}

	return 0;
}