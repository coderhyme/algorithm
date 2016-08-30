#include <cstdio>
#include <algorithm>

using namespace std;

int m, n;
int mat[1005][1005];
int a1[1005][1005];
int a2[1005][1005];
int b1[1005][1005];
int b2[1005][1005];

void buildCache() {
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            a1[i][j] = max(a1[i-1][j], a1[i][j-1]) + mat[i][j];
        }
    }

    for (int i=n; i>=1; --i) {
        for (int j=m; j>=1; --j) {
            a2[i][j] = max(a2[i+1][j], a2[i][j+1]) + mat[i][j];
        }
    }

    for (int i=n; i>=1; --i) {
        for (int j=1; j<=m; ++j) {
            b1[i][j] = max(b1[i+1][j], b1[i][j-1]) + mat[i][j];
        }
    }


    for (int i=1; i<=n; ++i) {
        for (int j=m; j>=1; --j) {
            b2[i][j] = max(b2[i-1][j], b2[i][j+1]) + mat[i][j];
        }
    }
}


int main()
{
    scanf("%d %d", &n, &m);

    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }

    buildCache();

    int ans = 0;

    for (int i=2; i<n; ++i) {
        for (int j=2; j<m; ++j) {
            ans = max(ans, max(a1[i-1][j] + a2[i+1][j] + b1[i][j-1] + b2[i][j+1],
                    a1[i][j-1] + a2[i][j+1] + b1[i+1][j] + b2[i-1][j]));
        }
    }

    printf("%d", ans);

	return 0;
}
