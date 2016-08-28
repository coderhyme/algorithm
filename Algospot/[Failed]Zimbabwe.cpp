#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

long long e;
char eStr[20];
int n;
int m;
int cache[1 << 15][20];

int countBit(int num) {
	int cnt = 0;
	for (; num; num &= (num - 1)) ++cnt;
	return cnt;
}

int solve(int used, int remain, bool canBorrow = false) {
	if (used == (1 << n) - 1) return remain == 0;

	int cnt = countBit(used);

	int& ret = cache[used][remain];
	if (ret != -1) return ret;
	ret = 0;

	long long zeros = 1LL;
	for (int i=n-cnt-1; i>0; --i) zeros *= 10LL;

	for (int i=0; i<n; ++i) {
		if (used & (1 << i)) continue;

		if (!canBorrow) {
			if (eStr[cnt] > eStr[i]) canBorrow = true;
			else if (eStr[cnt] < eStr[i]) continue;
		}

		const int nextRemain = ((eStr[i] - '0') * zeros + remain * 10) % m;
		ret += solve(used | (1 << i), nextRemain, canBorrow);
	}

	return ret;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("Zimbabwe.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		memset(cache, -1, sizeof(cache));

		scanf("%s %d", eStr, &m);
		n = strlen(eStr);
		e = atoll(eStr);

		printf("%d\n", solve(0, 0, 0) - 1);
	}

	return 0;
}
