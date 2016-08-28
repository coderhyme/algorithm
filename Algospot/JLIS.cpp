#include <cstdio>
#include <vector>

using namespace std;

int M, N;
vector<int> MNUM, NNUM;
vector<vector<int> > CACHE;

int solve(int a, int b, int num) {
	int& ret = CACHE[a][b];
	if (ret != -1) return ret;
	ret = 0;

	for (int i=a; i<N; ++i) {
		if (NNUM[i] > num) {
			ret = max(ret, solve(i+1, b, NNUM[i]) + 1);
		}
	}

	for (int i=b; i<M; ++i) {
		if (MNUM[i] > num) {
			ret = max(ret, solve(a, i+1, MNUM[i]) + 1);
		}
	}

	return ret;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("JLIS.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		scanf("%d %d", &N, &M);
		NNUM.resize(N);
		MNUM.resize(M);

		CACHE = vector<vector<int>>(N+1, vector<int>(M+1, -1));
		for (int i=0; i<N; ++i) scanf("%d", &NNUM[i]);
		for (int i=0; i<M; ++i) scanf("%d", &MNUM[i]);

		int ans = 0;
		for (int i=0; i<N; ++i) ans = max(ans, solve(i+1, 0, NNUM[i]) + 1);
		for (int i=0; i<M; ++i) ans = max(ans, solve(0, i+1, MNUM[i]) + 1);

		printf("%d\n", ans);
	}

	return 0;
}
