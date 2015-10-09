#include <iostream>
#include <string>
using namespace std;

int main()
{
	char c;
	string keyboard = "1234567890-=QWERTYUIOP[]\ASDFGHJKL;'ZXCVBNM,./";
	while (cin >> noskipws >> c) {
		if (c == EOF)
			return 0;
		if (c == ' ' || c == '\n')
			cout << c;
		else {
			size_t i = keyboard.find(c);
			cout << keyboard[i - 1];
		}
	}
	return 0;
}