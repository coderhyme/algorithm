#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 10000;

struct Tbit{
    int t[N + 1];

    void clear()
    {
        memset(t, 0, sizeof(t));
    }

    void insert(int x, int a)
    {
        for (; x <= N; x += x & (-x))
            t[x] = max(t[x], a);
    }

    int query(int x)
    {
        int res = 0;
        for (; x; x -= x & (-x))
            res = max(res, t[x]);
        return res;
    }
};

int main()
{
    Tbit t;
    t.clear();

    srand(time(NULL));
    vector<int> vec(100);

    for (int i=0; i<100; ++i) {
        vec[i] = rand() % N;
        printf("%4d ", vec[i]);
    }
    printf("\n");
    for (int i=0; i<100; ++i) {
        int s = t.query(vec[i]) + 1;
        printf("%4d ", s);
        t.insert(vec[i], s);
    }
    printf("\n");

	return 0;
}
