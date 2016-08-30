#include <cstdio>
#include <algorithm>

using namespace std;

const int CACHE_SIZE = 500;

int sushi[20][2];
int n, m;

int main()
{
#ifdef RUN_LOCAL
	freopen("Sushi.txt", "r", stdin);
#endif

	int tc;

	scanf("%d", &tc);

	while (tc--) {
	    scanf("%d %d", &n, &m);
	    m /= 100;

	    for (int i=0; i<n; ++i) {
	        scanf("%d %d", &sushi[i][0], &sushi[i][1]);
	        sushi[i][0] /= 100;
	    }

	    int cache[CACHE_SIZE] { 0 };

	    for (int i=1; i<=m; ++i) {
	        for (int j=0; j<n; ++j) {
	            if (sushi[j][0] > i) continue;
	            cache[i % CACHE_SIZE] = max(cache[i % CACHE_SIZE],
	                    cache[(i - sushi[j][0]) % CACHE_SIZE] + sushi[j][1]);
	        }
	    }

	    printf("%d\n", *max_element(cache, cache + CACHE_SIZE));
	}

	return 0;
}
