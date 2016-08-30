#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

string s;
unordered_set<string> suffixes;

bool checked[2][10001];

void solve(int end, const string& prev) {
    bool& c = checked[prev.length() - 2][end];
    if (c) return;
    c = true;

    for (int i=2; i<4; ++i) {
        if (end - i < 5) continue;
        string suffix = s.substr(end - i, i);
        if (prev == suffix) continue;
        suffixes.insert(suffix);
        solve(end - i, suffix);
    }
}

int main()
{
    cin >> s;

    solve(s.length(), "  ");

    vector<string> vec{ suffixes.begin(), suffixes.end() };
    sort(vec.begin(), vec.end());

    cout << vec.size() << endl;
    for (auto& ss : vec) cout << ss << endl;

	return 0;
}
