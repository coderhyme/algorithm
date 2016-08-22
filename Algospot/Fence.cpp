// Divide and conquer

/* 배운점 : Divide and conquer 구현시 반 열린 구간(half-open interval) 방식의
 * 인덱스 기반을 이용하면 무한루프에 빠지는 경우가 발생 할 수 있다.
 * 아래의 코드에서 solve함수의 e가 유효한 last index가 아닌 last index를 가리킨다면 문제가 되는 것
 */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int solve(const vector<int>& vec, int s, int e) {
	if (s == e) return vec[s];

	int ret = 0;

	int m = (s + e) / 2;

	int i = m, j = m + 1;
	int minHeight = 50000;

	while (i >= s || j <= e) {
		if (i >= s && (j == e - 1 || vec[i] > vec[j])) {
			minHeight = min(minHeight, vec[i]);
			--i;
		} else {
			minHeight = min(minHeight, vec[j]);
			++j;
		}

		ret = max(ret, minHeight * (j - i - 1));
	}

	return max(ret, max(solve(vec, s, m), solve(vec, m + 1, e)));
}

int main() {
	freopen("Fence.txt", "r", stdin);

	int tc;

	scanf("%d", &tc);

	while(tc--) {
		int n;
		vector<int> vec;

		scanf("%d", &n);

		while(n--) {
			int v;
			scanf("%d", &v);

			vec.push_back(v);
		}
		printf("%d\n", solve(vec, 0, vec.size() - 1));
	}

	return 0;
}
