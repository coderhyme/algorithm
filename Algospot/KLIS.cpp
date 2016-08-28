#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const long long MAX = 0xfffffffffLL;

int n;
int nums[505];
int dpLIS[505];
long long dpCnt[505];

int getLIS(int from) {
	int& ret = dpLIS[from];
	if (ret != -1) return ret;
	ret = 0;

	for (int i=from+1; i<n; ++i) {
		if (nums[from] < nums[i]) ret = max(ret, getLIS(i) + 1);
	}

	return ret;
}

void count() {
	memset(dpCnt, 0, sizeof(dpCnt));

	// 각 위치에서의 LIS를 이용하여 가능한 조합수를 미리 구해놓는다.
	// 현재 위치의 LIS가 4라면 뒤에 오는 LIS가 3인 모든 위치의 조합들을 더하면 되는것.
	for (int i=n-1; i>0; --i) {
		if (dpLIS[i] == 0) {
			dpCnt[i] = 1;
			continue;
		}
		for (int j=i+1; j<n; ++j) {
			if (nums[i] < nums[j] && dpLIS[i] - 1 == dpLIS[j]) {
				dpCnt[i] = min(MAX, dpCnt[i] + dpCnt[j]);
			}
		}
	}
}

// 전체 정렬을하면 선형시간에 결과를 만들수 있을듯하지만... 넘어가자.아래 시간복잡도는 n^2logn
void construct(int remain, int k, int from, vector<int>& result) {
	if (remain == -1) return;

	vector<pair<int, int>> vec;
	for (int i=from + 1; i<n; ++i) {
		if (nums[from] < nums[i] && dpLIS[i] == remain) vec.push_back({ nums[i], i });
	}
	sort(vec.begin(), vec.end());

	for (auto& p : vec) {
		if (dpCnt[p.second] >= k) {
			result.push_back(p.first);
			construct(remain - 1, k, p.second, result);
			break;
		} else {
			k -= dpCnt[p.second];
		}
	}
}

int main() {
#ifdef RUN_LOCALLY
	freopen("KLIS.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		memset(dpLIS, -1, sizeof(dpLIS));

		int k;
		scanf("%d %d", &n, &k);
		++n;

		for (int i=1; i<n; ++i) scanf("%d", &nums[i]);

		printf("%d\n", getLIS(0));

		count();

		vector<int> result;
		construct(getLIS(0) - 1, k, 0, result);

		for (int i : result) printf("%d ", i);
		printf("\n");
	}

	return 0;
}
