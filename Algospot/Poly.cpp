#include <cstdio>
#include <cstring>

using namespace std;

const int MOD = 10000000;

int dp[101][101];

int solve(int before, int remain) {
	if (remain == 0) return 1;
	if (remain == 1) return before;

	int& ref = dp[before][remain];
	if (ref != -1) return ref;
	ref = 0;

	for (int i=1; i<=remain; ++i) {
		ref = (ref + solve(i, remain - i) * (before + i - 1)) % MOD;
	}

	return ref;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("Poly.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	memset(dp, -1, sizeof(dp));

	while(tc--) {
		int n;
		scanf("%d", &n);

		int ans = 0;
		for (int i=1; i<=n; ++i) {
			ans = (ans + solve(i, n-i)) % MOD;
		}
		printf("%d\n", ans);
	}

	return 0;
}
