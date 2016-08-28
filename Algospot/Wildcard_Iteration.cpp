#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


string readStr() {
	char str[101];

	scanf("%s", str);

	return str;
}

bool solve(const string& p, const string& word) {
	char dp[101][101] { { 0 } };

	dp[0][0] = true;

	for (int i=0; p[i] == '*'; ++i) {
		dp[i+1][0] = true;
	}

	for (int i=1; i<=p.size(); ++i) {
		for (int j=1; j<=word.size(); ++j) {
			char a = p[i-1];
			char b = word[j-1];

			if (a == '*') {
				dp[i][j] = dp[i][j-1] || dp[i-1][j];
			} else if (a == '?' || a == b) {
				dp[i][j] = dp[i-1][j-1];
			}
		}
	}

	return dp[p.size()][word.size()];
}

int main() {
#ifdef RUN_LOCALLY
	freopen("Wildcard.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		vector<string> ans;

		string p = readStr();

		int n;

		scanf("%d", &n);

		while(n--) {
			string word = readStr();
			if (solve(p, word)) {
				ans.push_back(word);
			}
		}

		sort(ans.begin(), ans.end());

		for (const auto& s : ans) {
			printf("%s\n", s.c_str());
		}
	}

	return 0;
}
