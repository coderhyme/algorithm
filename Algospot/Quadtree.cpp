#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string solve(const string& str, int where) {
	if (str.length() == where) return "";

	if (str[where] != 'x') return string(1, str[where]);
	++where;

	string topLeft = solve(str, where);
	where += topLeft.size();

	string topRight = solve(str, where);
	where += topRight.size();

	string bottomLeft = solve(str, where);
	where += bottomLeft.size();

	string bottomRight = solve(str, where);

	return 'x' + bottomLeft + bottomRight + topLeft + topRight;
}

int main() {
	freopen("Quadtree.txt", "r", stdin);

	int tc;

	cin >> tc;

	while(tc--) {
		string str;

		cin >> str;

		cout << solve(str, 0) << endl;
	}

	return 0;
}
