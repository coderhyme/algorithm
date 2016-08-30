#include <iostream>
#include <algorithm>

#include <cstring>

using namespace std;

int n, t;
int a[100];
int cache[10010];
int cacheLen;

int longest(int from) {
    int& ret = cache[from];
    if (ret != -1) return ret;
    ret = 0;

    for (int i=from+1; i<cacheLen; ++i) {
        if (a[from % n] <= a[i % n]) ret = max(ret, longest(i) + 1);
    }

    return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));

    cin >> n >> t;

    for (int i=0; i<n; ++i) cin >> a[i];

    cacheLen = n * min(n, t);

    int ans = 0;

    for (int i=0; i<n; ++i)
        ans = max(ans, longest(i) + 1);

    if (t > n) {
        vector<int> v;
        unique_copy(a, a + n, back_inserter(v));
        int maxCnt = 0;
        for (int i : v) maxCnt = max(maxCnt, count(a, a + n, i));

        ans += maxCnt * (t - n);
    }

    cout << ans;

	return 0;
}
