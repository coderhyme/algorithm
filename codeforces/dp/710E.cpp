// 1. 문제를 제대로 읽지않아서 delete가 가능하다는걸 파악못함!
// 2. 복사후 한글자를 지우는게 더 빠른경우가 있다는걸 생각하지못함!

#include <iostream>
#include <algorithm>

using namespace std;

int n, x, y;
long long cache[10000001];

int main()
{
    cin >> n >> x >> y;

    int end = n % 2 ? n + 1 : n;
    for (int i=1; i<=end; ++i) {
        cache[i] = cache[i-1] + x;
        if (i % 2 == 0) {
            cache[i] = min(cache[i], cache[i / 2] + y);
            cache[i-1] = min(cache[i-1], cache[i] + x);
        }
    }

    cout << cache[n];

	return 0;
}
