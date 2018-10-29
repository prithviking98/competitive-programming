#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1000000007;

int main() {
	// freopen("temp.in", "r", stdin); // Comment out before submitting
	// freopen("temp.out", "w", stdout); // Comment out before submitting
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int test_cases;
	cin >> test_cases;
	for (int iter = 0; iter < test_cases; ++iter) {
		string s;
		cin >> s;
		vector<pair<int, int>> arr;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] != '.') {
				arr.emplace_back(i, s[i] - '0');
			}
		}
		bool flag = true;
		for (int i = 0; i < (int)arr.size() - 1; ++i) {
			if (arr[i].first + arr[i].second >= arr[i + 1].first - arr[i + 1].second) {
				flag = false;
				break;
			}
		}
		if (flag) {
			cout << "safe\n";
		}
		else {
			cout << "unsafe\n";
		}
	}
	return 0;
}
