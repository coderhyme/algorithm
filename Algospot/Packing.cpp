/**
 * 실수 : reconstruct 구현 실패!
 *
 * 배운점 : reconstruct 구현 시 solve를 재사용할 수 있음!
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N, W;
char names[101][22];
int size[101];
int desired[101];
int dp[101][1001];

int solve(int from, int capa) {
	if (from == N) return 0;

	int& ret = dp[from][capa];
	if (ret != -1) return ret;

	ret = solve(from + 1, capa);
	if (size[from] <= capa)
		ret = max(ret, solve(from + 1, capa - size[from]) + desired[from]);

	return ret;
}

void reconstruct(int from, int capa, vector<string>& result) {
	if (from == N) return;

	if (solve(from, capa) == solve(from + 1, capa)) {
		reconstruct(from + 1, capa, result);
	} else {
		result.push_back(names[from]);
		reconstruct(from + 1, capa - size[from], result);
	}
}

int main() {
#ifdef RUN_LOCALLY
	freopen("Packing.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		scanf("%d %d", &N, &W);

		for (int i=0; i<N; ++i) {
			scanf("%s %d %d", names[i], &size[i], &desired[i]);
		}

		memset(dp, -1, sizeof(dp));

		int ans = solve(0, W);

		vector<string> items;
		reconstruct(0, W, items);

		printf("%d %d\n", ans, items.size());

		for (auto& i : items) printf("%s\n", i.c_str());
	}

	return 0;
}
