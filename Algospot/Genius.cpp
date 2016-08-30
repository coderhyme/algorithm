#include <cstdio>

using namespace std;

int n, k, m;
int L[50];
double T[50][50];
int Q[10];

int main()
{
#ifdef RUN_LOCAL
	freopen("Genius.txt", "r", stdin);
#endif

	int tc;
	scanf("%d", &tc);

	while (tc--) {
	    scanf("%d %d %d", &n, &k, &m);

	    for (int i=0; i<n; ++i) scanf("%d", &L[i]);
	    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) scanf("%lf", &T[i][j]);
	    for (int i=0; i<m; ++i) scanf("%d", &Q[i]);

	    double prob[10][50] = { 0 };
	    prob[0][0] = 1.0;

	    for (int i=1; i<=k; ++i) {
            for (int b=0; b<n; ++b) prob[i % 10][b] = 0;
	        for (int a=0; a<n; ++a) {
	            if (L[a] > i) continue;
	            for (int b=0; b<n; ++b) {
	                prob[i % 10][b] += prob[(i - L[a]) % 10][a] * T[a][b];
	            }
	        }
	    }

	    for (int i=0; i<m; ++i) {
	        double sum = 0;
	        for (int j=0; j<L[Q[i]]; ++j)
	            if (k - j >= 0) sum += prob[(k - j) % 10][Q[i]];
	        printf("%.8f ", sum);
	    }
	    printf("\n");
	}

	return 0;
}
