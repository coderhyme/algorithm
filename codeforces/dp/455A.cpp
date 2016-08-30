#include <iostream>
#include <algorithm>

using namespace std;

int cnt[100001];

int main()
{
    int n;

    cin >> n;

    while(n--) {
        int v;
        cin >> v;
        ++cnt[v];
    }

    long long choose = 0;
    long long notChoose = 0;

    for (int i=1; i<=100000; ++i) {
        long long nextChoose = notChoose + cnt[i] * (long long)i;

        notChoose = max(notChoose, choose);
        choose = nextChoose;
    }

    cout << max(choose, notChoose);

	return 0;
}
