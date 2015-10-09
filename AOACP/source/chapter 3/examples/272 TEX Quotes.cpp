#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	char c;
	bool left_quote = true;
	while (cin >> noskipws >> c) {
		if (c == EOF)
			return 0;
		if (c == '"') {
			if (left_quote) {
				cout << "``";
				left_quote = !left_quote;
			} else {
				cout << "''";
				left_quote = !left_quote;
			}
		} else
			cout << c;
	}
	return 0;
}