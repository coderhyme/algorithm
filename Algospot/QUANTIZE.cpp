#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

const int INF = 987654321;
int N, S;
vector<int> nums;
int dp[100][11];

// optimized solution
/**
 * 아래 sigma는 i=a부터 b까
 * ∑(A[i]-m)^2 = ∑(A[i]^2 - 2*m*A[i] + m^2)
 *             = ∑(A[i]^2) - 2*m*∑(A[i]) + m^2(b-a+1)
 *
 *
 */
int pSum[101];
int pSqSum[101];

void precalc() {
	pSum[0] = nums[0];
	pSqSum[0] = nums[0] * nums[0];
	for (int i=1; i<N; ++i) {
		pSum[i] = pSum[i-1] + nums[i];
		pSqSum[i] = pSqSum[i-1] + nums[i] * nums[i];
	}
}

int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo-1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo-1]);

	int m = int(0.5 + (double)sum / (hi - lo + 1));

	return sqSum - 2 * m * sum + m * m * (hi - lo + 1);
}

// naive!
int getAverage(double sum, int count) {
	return sum / count + 0.5;
}

int minErrorNaive(int from, int to) {
	int sum = accumulate(&nums[from], &nums[to + 1], 0);

	int average = getAverage(sum, to - from + 1);

	int squareSum = 0;

	for (int j=from; j<=to; ++j) {
		squareSum += (average - nums[j]) * (average - nums[j]);
	}

	return squareSum;
}

int solve(int from, int left) {
	// S가 N보다 작다는 조건이 존재하지 않으므로 left가 0일때만 0을 리턴할 필요가 없었다!
	if (from == N/* && left == 0 */) return 0;
	if (left == 0) return INF;

	int& ret = dp[from][left];
	if (ret != -1) return ret;
	ret = INF;

	for (int i=from; i<N; ++i) {
		ret = min(ret, solve(i + 1, left - 1) + minErrorNaive(from, i));
	}

	return ret;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("QUANTIZE.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		scanf("%d %d", &N, &S);

		nums.resize(N);

		for (int i=0; i<N; ++i) scanf("%d", &nums[i]);

		memset(dp, -1, sizeof(dp));

		sort(nums.begin(), nums.end());

		precalc();

		printf("%d\n", solve(0, S));
	}

	return 0;
}
