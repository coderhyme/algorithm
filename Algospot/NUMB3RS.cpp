#include <cstdio>
#include <vector>

using namespace std;

int n, d, p;
vector<double> acc;
vector<int> linkCount;
int adj[50][50];

void solve(int dayLeft) {
	if (dayLeft == 0) return;

	vector<double> next(n, 0.0);

	for (int i=0; i<n; ++i) {
		for (int j=0; j<n; ++j) {
			if (adj[i][j]) {
				next[j] += acc[i] / linkCount[i];
			}
		}
	}

	swap(next, acc);

	solve(dayLeft - 1);
}

int main() {
#ifdef RUN_LOCALLY
	freopen("NUMB3RS.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		scanf("%d %d %d", &n, &d, &p);

		linkCount.resize(n);

		for (int i=0; i<n; ++i) {
			int cnt = 0;
			for (int j=0; j<n; ++j) {
				scanf("%d", &adj[i][j]);
				if (adj[i][j]) ++cnt;
			}

			linkCount[i] = cnt;
		}

		acc = vector<double>(n, 0.0);
		acc[p] = 1.0;

		solve(d);

		int t;
		scanf("%d", &t);

		while(t--) {
			int q;
			scanf("%d", &q);
			printf("%.8lf ", acc[q]);
		}
		printf("\n");
	}

	return 0;
}
