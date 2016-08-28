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
	if (curIndex == sentence.size()) return 0;

	double& ret = dp[curIndex][prevWord];
	if (ret != 1.0) return ret; // 확률의 로그값들은 모두 음수일것이다 확률이 모두 1보다 작은 값이기때문!
	ret = -1e200; // 음 무한대에 해당하는

	auto& choice = choices[curIndex][prevWord];

	const int curWord = sentence[curIndex];

	for(int i=1; i<=m; ++i) {
		auto value = adjProb[prevWord][i] + cateProb[i][curWord] +
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

void resetCache() {
	for (int i=0; i<105; ++i) {
		for (int j=0; j<505; ++j) {
			dp[i][j] = 1.0;
		}
	}
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
			double value;
			scanf("%lf", &value);
			adjProb[i][j] = log(value);
		}
	}

	for (int i=1; i<=m; ++i) {
		for (int j=1; j<=m; ++j) {
			double value;
			scanf("%lf", &value);
			cateProb[i][j] = log(value);
		}
	}

	while(q--) {
		resetCache();
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
