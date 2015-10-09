#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
//#define DRAFT

int main()
{
	string origin  = "AEHIJLMOSTUVWXYZ12358";
	string reverse = "A3HILJMO2TUVWXY51SEZ8";
	string line;
	string outputs[4] = { 
		" -- is not a palindrome.\n",
		" -- is a regular palindrome.\n",
		" -- is a mirrored string.\n",
		" -- is a mirrored palindrome.\n"
	};
#ifdef DRAFT
	ifstream in("../../tests/401.in");
	if (!in.is_open()) {
		cerr << "WTF!" << endl;
		return -1;
	}
	cin.rdbuf(in.rdbuf());
#endif
	while (getline(cin, line)) {
		vector<char> vec;
		stack<char> stak;
		for (char c : line) {
			vec.push_back(c);
			stak.push(c);
		}
		bool is_mirrored = true, is_palindrome = true;
		for (char c1 : vec) {
			char c2 = stak.top();
			stak.pop();
			if (c1 != c2) {
				is_palindrome = false;
			}
			size_t i = origin.find(c1);
			if (i == string::npos)
				is_mirrored = false;
			else {
				if (reverse[i] != c2)
					is_mirrored = false;
			}
			if (!is_palindrome && !is_mirrored) {
				break;
			}
		}
		if (is_palindrome && !is_mirrored)
			cout << line << outputs[1] << endl;
		else if (!is_palindrome && is_mirrored)
			cout << line << outputs[2] << endl;
		else if (is_palindrome && is_mirrored)
			cout << line << outputs[3] << endl;
		else
			cout << line << outputs[0] << endl;
	}
	return 0;
}