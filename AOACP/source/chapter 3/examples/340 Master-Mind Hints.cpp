#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
//#define DRAFT

int main()
{
#ifdef DRAFT
	ifstream in("../../tests/340.in");
	cin.rdbuf(in.rdbuf());
#endif
	string len;
	int round = 1;
	while (getline(cin, len)) {
		int n = stoi(len);
		if (!n) // end of input
			break;

		vector<int> secret;
		vector<int> s_count(10);
		string line;
		getline(cin, line);
		stringstream ss;
		ss << line;
		for (int i = 0; i < n; ++i) {
			int num; 
			ss >> num;
			secret.push_back(num);
			++s_count[num];
		}
		cout << "Game " << round << ":" << endl;
		
		while (getline(cin, line)) {
			stringstream ss;
			ss << line;
			vector<int> guess;
			vector<int> g_count(10);
			int strong_match = 0;
			for (int i = 0; i < n; ++i) {
				int num;
				ss >> num;
				guess.push_back(num);
				++g_count[num];
				if (num == secret[i])
					++strong_match;
			}
			if (g_count[0] == n) { // end of this round
				++round;
				break;
			}
			int match = 0;
			for (int i = 1; i < 10; ++i) {
				int min = s_count[i];
				if (g_count[i] < min)
					min = g_count[i];
				match += min;
			}
			cout << "    (" << strong_match << ","
				<< match - strong_match << ")" << endl;
		}
	}
	return 0;
}