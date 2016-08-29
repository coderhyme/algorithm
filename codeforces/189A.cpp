#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	int len[3];

	scanf("%d %d %d %d", &n, &len[0], &len[1], &len[2]);

	vector<int> cache(n + 1, -1);
	cache[0] = 0;

	for (int i=1; i<=n; ++i) {
		for (int j=0; j<3; ++j) {
			if (i < len[j]) continue;
			int prev = cache[i - len[j]];
			if (prev == -1) continue;
			cache[i] = max(cache[i], prev + 1);
		}
	}

	printf("%d", cache[n]);

	return 0;
}
