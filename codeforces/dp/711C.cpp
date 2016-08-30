#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int n, m, k;
int c[101];
int p[101][101];
long long cache[110][110][110];

int main()
{
    cin >> n >> m >> k;

    for (int i=1; i<=n; ++i) cin >> c[i];
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) cin >> p[i][j];

    vector<int> colors;
    for (int i=1; i<=m; ++i) colors.push_back(i);

    for (int i=0; i<=100; ++i) for (int j=0; j<=100; ++j) for (int a=0; a<=100; ++a) cache[i][j][a] = INF;

    if (c[1]) cache[1][1][c[1]] = 0;
    else {
        for (int i=1; i<=m; ++i) cache[1][1][i] = p[1][i];
    }

    for (int i=2; i<=n; ++i) {
        vector<int> possible = c[i] ? vector<int>{ c[i] } : colors;

        for (int j=1; j<=k; ++j) {
            for (int a=1; a<=m; ++a) {
                for (int b : possible) {
                    auto& here = cache[i][j][b];
                    int cost = (c[i] ? 0 : p[i][b]);
                    if (a != b) {
                        here = min(here, cache[i-1][j-1][a] + cost);
                    } else {
                        here = min(here, cache[i-1][j][a] + cost);
                    }
                }
            }
        }
    }

    long long ans = *min_element(cache[n][k], cache[n][k] + m + 1);

    cout << (ans == INF ? -1 : ans);

	return 0;
}
