#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int m, s;
bool cache[101][901];
vector<int> nums;

bool solveSmallest(int len, int remain, string& result) {
	if (remain == 0) {
		result += string(len, '0');
		return true;
	}
	if (len == 0) return false;

	bool& ret = cache[len][remain];
	if (ret) return false;

	for (int i : nums) {
		result.push_back('0' + i);
		if (solveSmallest(len - 1, remain - i, result)) return true;
		result.pop_back();
	}

	ret = true;
	return false;
}

string smallest() {
	string result;

	for (int i=0; i<=9; ++i) nums.push_back(i);

	for (int i=1; i<=9; ++i) {
		result.push_back('0' + i);
		if (solveSmallest(m - 1, s - i, result)) return result;
		result.pop_back();
	}

	return "-1";
}

bool solveLargest(int len, int remain, string& result) {
	if (remain == 0) {
		result += string(len, '0');
		return true;
	}
	if (len == 0) return false;

	bool& ret = cache[len][remain];
	if (ret) return false;

	for (int i=9; i>=0; --i) {
		result.push_back('0' + i);
		if (solveLargest(len - 1, remain - i, result)) return true;
		result.pop_back();
	}

	ret = true;
	return false;
}

string largest() {
	string result;

	reverse(nums.begin(), nums.end());

	for (int i=9; i>0; --i) {
		result.push_back('0' + i);
		if (solveSmallest(m - 1, s - i, result)) return result;
		result.pop_back();
	}

	return "-1";
}


int main() {
	scanf("%d %d", &m, &s);

	string s = smallest();
	string l = largest();
	printf("%s %s", s.c_str(), l.c_str());

	return 0;
}
