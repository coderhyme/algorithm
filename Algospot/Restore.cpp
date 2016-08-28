// 실수 : vector<string> 사용시 string 접근할때 인덱스를 vec.size()를 해야하는데 vec[i].size()를 함...
// 멍청한 실수..

/**
 * 아래의 솔루션은 이전의 선택된 문자열과 남은 문자열들 정보를 기반으로 만들수 있는 최소문자열을 구하는 방식으로 구현되었지만,
 * 거꾸로 생각해서 문자열들의 중첩의 최대값을 모든 문자열의 길이의 합에서 빼는 방법도 가능하다!
 */
#include <cstdio>
#include <cstring>

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 987654321;

vector<string> pieces;
int dupLength[20][20];
int cache[1<<16][20];

int solve(int used, int prev) {
	if (used == (1 << pieces.size()) - 1) return 0;

	int& ret = cache[used][prev+1];
	if (ret != -1) return ret;
	ret = INF;

	for (int i=0; i<pieces.size(); ++i) {
		if (used & (1 << i)) continue;

		int added = prev == -1 ? pieces[i].length() : pieces[i].length() - dupLength[prev][i];

		ret = min(ret, solve(used | (1 << i), i) + added);
	}

	return ret;
}

int getDup(const string& word, const string& follower) {
	for (int i=min(word.length(), follower.length())-1; i>0; --i) {
		if (word.substr(word.length() - i, i) == follower.substr(0, i)) return i;
	}

	return 0;
}

void calcDup() {
	memset(dupLength, -1, sizeof(dupLength));
	int n = pieces.size();
	for (int i=0; i<n; ++i) {
		for (int j=i+1; j<n; ++j) {
			dupLength[i][j] = getDup(pieces[i], pieces[j]);
			dupLength[j][i] = getDup(pieces[j], pieces[i]);
		}
	}
}

void read() {
	pieces.clear();

	vector<string> vec;
	int n;

	scanf("%d", &n);

	while(n--) {
		char str[50];
		scanf("%s", str);
		vec.push_back(str);
	}

	sort(vec.begin(), vec.end(), [](const string& lhs, const string& rhs){
		return lhs.length() < rhs.length();
	});

	for (int i=0; i<vec.size(); ++i) {
		bool isSub = false;
		for (int j=i+1; j<vec.size(); ++j) {
			if (vec[j].find(vec[i]) != string::npos) {
				isSub = true;
				break;
			}
		}

		if (!isSub) pieces.push_back(vec[i]);
	}
}

void reconstruct(int used, int prev, string& result) {
	if (used == (1 << pieces.size()) - 1) return;

	for (int i=0; i<pieces.size(); ++i) {
		if (used & (1 << i)) continue;
		int added = prev == -1 ? pieces[i].length() : pieces[i].length() - dupLength[prev][i];
		if (solve(used, prev) == solve(used | (1 << i), i) + added) {
			result += pieces[i].substr(pieces[i].length() - added, added);
			reconstruct(used | (1 << i), i, result);
			return;
		}
	}
}

int main() {
#ifdef RUN_LOCALLY
	freopen("Restore.txt", "r", stdin);
#endif
	int tc;

	scanf("%d", &tc);

	while(tc--) {
		read();
		calcDup();

		memset(cache, -1, sizeof(cache));
		solve(0, -1);

		string result;
		reconstruct(0, -1, result);
		printf("%s\n", result.c_str());
	}

	return 0;
}
