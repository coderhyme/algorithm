// 못풀었다!!!!!!!!!

#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

const int MAX = 1000000005;

int cnt[51];
int n, p, l;

void precalc() {
	cnt[0] = 1;

	for (int i=0; i<50; ++i) {
		cnt[i+1] = min(MAX, cnt[i] * 2 + 2);
	}
}

char solve(const string& str, int remain, int k) {
	if (remain == 0) return str[k];

	for (char ch : str) {
		if (ch == 'X' || ch == 'Y') {
			if (k >= cnt[remain]) k -= cnt[remain];
			else if (ch == 'X') return solve("X+YF", remain - 1, k);
			else return solve("FX-Y", remain - 1, k);
		} else if (k > 0) {
			--k;
		} else {
			return ch;
		}
	}
	return '?';
}

int main() {
#ifdef RUN_LOCALLY
	freopen("Dragon.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	precalc();

	while(tc--) {
		scanf("%d %d %d", &n, &p, &l);

		for (int i=p; i<p+l; ++i) {
			printf("%c", solve("FX", n, i-1));
		}
		printf("\n");
	}

	return 0;
}
