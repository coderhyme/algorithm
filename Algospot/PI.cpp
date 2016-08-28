#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int INF = 987654321;

int N;
char INPUT[10001];
char DIFF[10001][3];
int CACHE[10001];

int calcDifficulty(int where, int len) {
	const int invalidGap = -100;

	if (where + len > N) return 10;

	int gap = INPUT[where] - INPUT[where+1];
	int nums = 1 << (INPUT[0] - '0');
	bool containsOnlyTwoNumbers = true;

	for (int i=1; i<len; ++i) {
		if (gap != INPUT[where+i-1] - INPUT[where+i]) gap = invalidGap;
		nums |= 1 << (INPUT[where+i] - '0');
		containsOnlyTwoNumbers &= INPUT[where+i] == INPUT[where+(i%2)];
	}

	if (gap != invalidGap) {
		if (gap == 0) return 1;
		if (abs(gap) == 1) return 2;
		return 5;
	}

	if (containsOnlyTwoNumbers) return 4;

	return 10;
}

void fillDifficulties() {
	for (int i=0; i<N; ++i) {
		for (int j=0; j<3; ++j) {
			DIFF[i][j] = calcDifficulty(i, j+3);
		}
	}
}

int solve(int from) {
	if (from == N) return 0;
	if (from > N) return INF;

	int& ret = CACHE[from];
	if (ret != -1) return ret;
	ret = INF;

	for (int i=0; i<3; ++i) {
		ret = min(ret, solve(from+i+3) + DIFF[from][i]);
	}

	return ret;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("PI.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		scanf("%s", INPUT);
		N = strlen(INPUT);

		memset(CACHE, -1, sizeof(CACHE));

		fillDifficulties();

		printf("%d\n", solve(0));
	}

	return 0;
}
