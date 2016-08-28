#include <cstdio>
#include <vector>

using namespace std;

const int INF = 987654321;

int n;
int nums[55];
int cache[50][50];

void clearCache() {
	for (int i=0; i<50; ++i) {
		for (int j=0; j<50; ++j) cache[i][j] = -INF;
	}
}

int solve(int l, int r) {
	int remain = r - l + 1;

	if (remain == 1) return nums[l];
	if (remain == 0) return 0;
	if (remain < 0) return -INF;

	int& ret = cache[l][r];
	if (ret != -INF) return ret;

	ret = max(ret, nums[l] - solve(l + 1, r));
	ret = max(ret, nums[r] - solve(l, r - 1));
	ret = max(ret, -solve(l + 2, r));
	ret = max(ret, -solve(l, r - 2));

	return ret;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("NumberGame.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		scanf("%d", &n);

		for (int i=0; i<n; ++i) scanf("%d", &nums[i]);

		clearCache();

		printf("%d\n", solve(0, n-1));
	}

	return 0;
}
