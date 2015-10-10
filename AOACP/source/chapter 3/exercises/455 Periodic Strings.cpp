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
	ifstream in("../../tests/455.in");
	cin.rdbuf(in.rdbuf());
#endif

	string str;
	getline(cin, str);
	int n = stoi(str);
	while (n--) {
		getline(cin, str);
		getline(cin, str);
		string period = str.substr (0, 1);
		int iter = 0;
		int step = period.size();
		while (iter != str.size()) {
			if (period == str.substr(iter, step) && iter + step <= str.size())
				iter += step;
			else {
				period = str.substr(0, iter + 1);
				step = period.size();
				iter = 0;
			}
		}
		cout << period.size() << endl << endl;
	}

	return 0;
}