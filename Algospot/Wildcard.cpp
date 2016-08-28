#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string WC;
string WORD;

char dp[101][101];

string readStr() {
	char str[101];

	scanf("%s", str);

	return str;
}

bool solve(int a, int b) {
	if (a == WC.size() && b == WORD.size()) return true;
	if (a == WC.size() || b > WORD.size()) return false;

	auto& ret = dp[a][b];
	ret = false;

	if (WC[a] == '*') {
		ret = solve(a + 1, b) || solve(a, b + 1);
	} else if (WC[a] == '?' || (b < WORD.size() && WC[a] == WORD[b])) {
		ret = solve(a + 1, b + 1);
	}

	return ret;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("Wildcard.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		vector<string> ans;

		WC = readStr();

		int n;

		scanf("%d", &n);

		while(n--) {
			WORD = readStr();
			memset(dp, -1, sizeof(dp));
			if (solve(0, 0)) {
				ans.push_back(WORD);
			}
		}

		sort(ans.begin(), ans.end());

		for (const auto& s : ans) {
			printf("%s\n", s.c_str());
		}
	}

	return 0;
}
