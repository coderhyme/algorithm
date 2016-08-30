#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int c[501];
int cache[501][501];

int solve(int i, int j) {
    if (i >= j) return 1;

    int& ret = cache[i][j];
    if (ret != -1) return ret;
    ret = 987654321;

    for (int k=i; k<j; ++k) {
        ret = min(ret, solve(i, k) + solve(k + 1, j));
    }

    if (c[i] == c[j]) ret = min(ret, solve(i+1, j-1));

    return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));

    int n;
    scanf("%d", &n);

    for (int i=0; i<n; ++i) scanf("%d", &c[i]);

    printf("%d", solve(0, n-1));
	return 0;
}
