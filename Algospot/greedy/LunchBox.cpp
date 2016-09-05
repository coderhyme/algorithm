#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

int main()
{
#ifdef RUN_LOCAL
	freopen("LunchBox.txt", "r", stdin);
#endif

	int tc;
	scanf("%d", &tc);

	while (tc--) {
	    int n; scanf("%d", &n);
        vector<PII> vec(n);

        for (int i=0; i<n; ++i) scanf("%d", &vec[i].second);
        for (int i=0; i<n; ++i) scanf("%d", &vec[i].first);

	    sort(vec.begin(), vec.end(), greater<PII>());

	    int ans = 0;
	    int micro = 0;

	    for (const auto& p : vec) {
	        micro += p.second;

	        ans = max(ans, micro + p.first);
	    }
	    printf("%d\n", ans);
	}

	return 0;
}
