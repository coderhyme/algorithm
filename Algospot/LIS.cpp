#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> NUMS;
vector<int> DP;

int solve(int from) {
//	배운점 : from은 항상 N보다 작은것이 보장되므로 아래의 base case는 의미가 없다.
//	if (from == N) return 0;

	int& ret = DP[from];
	if (ret != -1) return ret;

	ret = 0;
	for (int i=from + 1; i<N; ++i) {
		if (NUMS[from] < NUMS[i]) {
			ret = max(ret, solve(i) + 1);
		}
	}

	return ret;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("LIS.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	NUMS.push_back(0);

	while(tc--) {
		scanf("%d", &N);
		++N;

		NUMS.resize(N);

		for (int i=1; i<N; ++i) {
			scanf("%d", &NUMS[i]);
		}

		DP = vector<int>(N, -1);

		printf("%d\n", solve(0));
	}

	return 0;
}
