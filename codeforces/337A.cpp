// http://codeforces.com/problemset/problem/337/A

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n, m;
	vector<int> f;

	scanf("%d %d", &n, &m);

	f.resize(m);
	for (int i=0; i<m; ++i) scanf("%d", &f[i]);

	sort(f.begin(), f.end());

	int ans = 20000;
	for (int i=0; i<=m-n; ++i) {
	    ans = min(ans, f[i+n-1] - f[i]);
	}

	printf("%d\n", ans);

	return 0;
}
