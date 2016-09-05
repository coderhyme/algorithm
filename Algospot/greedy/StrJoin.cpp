#include <cstdio>
#include <queue>
#include <functional>

using namespace std;

int main()
{
#ifdef RUN_LOCAL
	freopen("StrJoin.txt", "r", stdin);
#endif

	int tc;
	scanf("%d", &tc);

	while (tc--) {
	    int n;
	    priority_queue<int, vector<int>, greater<int>> q;

	    scanf("%d", &n);

	    while (n--) {
	        int v;
	        scanf("%d", &v);
	        q.push(v);
	    }

	    int ans = 0;

	    while (q.size() > 1) {
	        int next = q.top();
	        q.pop();
	        next += q.top();
	        q.pop();
	        q.push(next);
	        ans += next;
	    }

	    printf("%d\n", ans);
	}

	return 0;
}
