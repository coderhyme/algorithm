#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
	int ans = 0;

	int n;

	int prev = -1;
	int cur = 0;

	scanf("%d", &n);

	int cnt = 0;

	while(n--) {
	    scanf("%d", &cur);

	    if (prev <= cur) ++cnt;
	    else cnt = 1;

	    ans = max(ans, cnt);

	    prev = cur;
	}

	printf("%d", ans);

	return 0;
}
