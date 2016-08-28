/**
 * 1. reconstruct 한번에 구현 실패. 별도의 배열을 사용하는걸 고려하지 않았음!!
 * 2. log를 이용하는 것이 좋음. 소수점 곱셈이 중첩될수록 값이 너무작아질수 있는 문제가 발생할 수 있음(언더플로우)!!
 *
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>

using namespace std;

vector<string> words;
unordered_map<string, int> dict;
int m, q;
double adjProb[505][505];
double cateProb[505][505];
vector<int> sentence;
double dp[105][505];
int choices[105][505];

double solve(int curIndex, int prevWord) {
	if (curIndex == sentence.size()) return 1.0;

	double& ret = dp[curIndex][prevWord];
	if (ret >= 0.0) return ret;
	ret = 0.0;

	auto& choice = choices[curIndex][prevWord];

	const int curWord = sentence[curIndex];

	for(int i=1; i<=m; ++i) {
		auto value = adjProb[prevWord][i] * cateProb[i][curWord] *
				solve(curIndex + 1, i);

		if (ret < value) {
			ret = value;
			choice = i;
		}
	}

	return ret;
}

void reconstruct(int curIndex, int prevWord) {
	if (curIndex == sentence.size()) return;

	const int curWord = choices[curIndex][prevWord];

	printf("%s ", words[curWord].c_str());
	reconstruct(curIndex + 1, curWord);
}

int main() {
#ifdef RUN_LOCALLY
	freopen("OCR.txt", "r", stdin);
#endif

	scanf("%d %d", &m, &q);
	words.push_back("");

	for (int i=1; i<=m; ++i) {
		char word[30];
		scanf("%s", word);
		dict.emplace(word, i);
		words.push_back(word);
	}

	for (int i=0; i<=m; ++i) {
		for (int j=1; j<=m; ++j) {
			scanf("%lf", &adjProb[i][j]);
		}
	}

	for (int i=1; i<=m; ++i) {
		for (int j=1; j<=m; ++j) {
			scanf("%lf", &cateProb[i][j]);
		}
	}

	while(q--) {
		memset(dp, -1, sizeof(dp));
		int n;
		scanf("%d", &n);

		sentence.clear();
		while(n--) {
			char word[30];
			scanf("%s", word);
			sentence.push_back(dict[word]);
		}

		solve(0, 0);
		reconstruct(0, 0);
		printf("\n");
	}

	return 0;
}
