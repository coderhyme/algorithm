// �̹����� O(N)���� Ǯ�� �ִ� ���� ����...
// 0�� -1�� �ٲ� �����ϸ� ���� min sum sequence�� ������ �� ����.
//#include <cstdio>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//int main()
//{
//    int n;
//    vector<int> num, ps;
//
//    scanf("%d", &n);
//
//    num.resize(n+1);
//    ps.resize(n+1);
//
//    for (int i=1; i<=n; ++i) scanf("%d", &num[i]);
//
//    partial_sum(num.begin()+1, num.end(), ps.begin()+1);
//
//    const int base = accumulate(num.begin(), num.end(), 0);
//    int ans = 0;
//
//    for (int i=1; i<=n; ++i) {
//        for (int j=i; j<=n; ++j) {
//            const int width = j - i + 1;
//
//            ans = max(ans, base - (ps[j] - ps[i-1]) * 2 + width);
//        }
//    }
//
//    printf("%d", ans);
//
//	return 0;
//}

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    vector<int> num;

    scanf("%d", &n);

    num.resize(n);
    int cnt = 0;

    for (int i=0; i<n; ++i) {
        int v;
        scanf("%d", &v);
        if (v == 1) ++cnt;
        else v = -1;

        num[i] = v;
    }

    int minSum = 0;
    int curSum = 0;
    int start = 0;
    int end = 1;
    int from = 0;

    for (int i=0; i<n; ++i) {
        curSum += num[i];

        if (minSum > curSum) {
            minSum = curSum;
            start = from;
            end = i + 1;
        }

        if (curSum > 0) {
            curSum = 0;
            from = i + 1;
        }
    }

    int cntZero = count(num.begin() + start, num.begin() + end, -1);
    int cntOne = count(num.begin() + start, num.begin() + end, 1);


    printf("%d", cnt - cntOne + cntZero);
    return 0;
}
