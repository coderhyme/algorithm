#include <cstdio>
#include <cstring>

using namespace std;

const long MOD = 1000000007;

int N;
int dp[101];

int precalc(int left) {
	if (left < 0) return 0;

	int& ret = dp[left];
	if (ret != -1) return ret;

	return ret = (precalc(left - 2) + precalc(left - 1)) % MOD;
}

int solve() {
	if (N % 2 == 0) {
		return ((long)dp[N] - dp[N / 2 - 1] - dp[N / 2] + MOD * 2) % MOD;
	}

	return ((long)dp[N] - dp[N / 2] + MOD) % MOD;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("AsymTiling.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		scanf("%d", &N);

		memset(dp, -1, sizeof(dp));
		dp[0] = 1;
		dp[1] = 1;

		precalc(100);

		printf("%d\n", solve());
	}

	return 0;
}
