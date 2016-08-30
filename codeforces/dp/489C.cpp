// O(n)에 풀수있는 방법이 있음.....

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int m, s;
bool cache[101][901];
vector<int> nums;

bool solve(int len, int remain, string& result) {
    if (remain == 0) {
        result += string(len, '0');
        return true;
    }
    if (len == 0) return false;

    bool& ret = cache[len][remain];
    if (ret) return false;

    for (int i : nums) {
        result.push_back('0' + i);
        if (solve(len - 1, remain - i, result)) return true;
        result.pop_back();
    }

    ret = true;
    return false;
}

string smallest() {
    string result;

    for (int i=0; i<=9; ++i) nums.push_back(i);

    for (int i=1; i<=9; ++i) {
        result.push_back('0' + i);
        if (solve(m - 1, s - i, result)) return result;
        result.pop_back();
    }

    if (m == 1 && s == 0) return "0";

    return "-1";
}

string largest() {
    string result;

    reverse(nums.begin(), nums.end());

    for (int i=9; i>0; --i) {
        result.push_back('0' + i);
        if (solve(m - 1, s - i, result)) return result;
        result.pop_back();
    }

    if (m == 1 && s == 0) return "0";

    return "-1";
}


int main() {
    scanf("%d %d", &m, &s);

    string s = smallest();
    string l = largest();
    printf("%s %s", s.c_str(), l.c_str());

    return 0;
}
