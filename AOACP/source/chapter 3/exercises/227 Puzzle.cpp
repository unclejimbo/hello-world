#include <iostream>
#include <string>

#define DRAFT
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

	string line;
	getline(cin, line);
	int n = stoi(line);
	while (n--) {
		getline(cin, line);
		
	}

	return 0;
}