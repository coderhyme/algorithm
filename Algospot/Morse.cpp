#include <cstdio>
// 아래에서는 n과 m의 남은 수를 이용하여 가능한 조합의 수를 계산했지만,
// 이항계수 혹은 조합을 이용하여 계산하는 것도 가능.
#include <cstring>
#include <algorithm>

using namespace std;

int dp[101][101];

int calc(int n, int m) {
	if (n == 0 || m == 0) return 1;

	auto& ret = dp[n][m];
	if (ret != -1) return ret;
	ret = min(1000000005, calc(n-1, m) + calc(n, m-1));

	return ret;
}

void solve(int n, int m, int k) {
	// 왜 n이 0일때만 확인하면 함수의 종료가 보장이되는 것일까???
	// 첫 솔루션에서는 n,m,k 모두 확인했었음...
	// 항상 조합의 수가 k보다 크거나 같도 유도가 되기때문이라고 볼수 있을려나... 고민이 조금 더필
	if (n == 0) {
		while (m--) printf("o");
		return;
	}

	if (calc(n - 1, m) >= k) {
		printf("-");
		solve(n - 1, m, k);
	} else {
		printf("o");
		solve(n, m - 1, k - calc(n - 1, m));
	}
}

int main() {
#ifdef RUN_LOCALLY
	freopen("Morse.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	memset(dp, -1, sizeof(dp));

	while(tc--) {
		int n, m, k;

		scanf("%d %d %d", &n, &m, &k);

		solve(n, m, k);
		printf("\n");
	}
	return 0;
}
