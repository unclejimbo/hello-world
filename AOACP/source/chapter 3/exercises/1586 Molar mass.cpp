#include <iostream>
#include <string>
#include <cmath>

#define DRAFT
#ifdef DRAFT
#include <fstream>
#endif

using namespace std;

int main()
{
#ifdef DRAFT
	ifstream in("../../tests/1586.in");
	cin.rdbuf(in.rdbuf());
#endif

	const double C_MASS = 12.01; 
	const double N_MASS = 14.01;
	const double H_MASS = 1.008;
	const double O_MASS = 16.00;

	string line;
	getline(cin, line);
	int n = stoi(line);
	for (int i = 0; i < n; ++i) {
		getline(cin, line);
		char last = 0;
		double mass = 0;
		int count = 0, decim = 0;
		for (auto iter = line.rbegin(); iter != line.rend(); ++iter) {
			if (*iter == 'C') {
				if (count == 0)
					count = 1;
				mass += C_MASS * count;
				count = decim = 0;
			}
			else if (*iter == 'H') {
				if (count == 0)
					count = 1;
				mass += H_MASS * count;
				count = decim = 0;
			}
			else if (*iter == 'N') {
				if (count == 0)
					count = 1;
				mass += N_MASS * count;
				count = decim = 0;
			}
			else if (*iter == 'O') {
				if (count == 0)
					count = 1;
				mass += O_MASS * count;
				count = decim = 0;
			}
			else {
				int num = *iter - '0';
				count += num * pow(10, decim++);
			}
		}
		
		cout.precision(3);
		cout << fixed << mass << endl;
	}

	return 0;
}