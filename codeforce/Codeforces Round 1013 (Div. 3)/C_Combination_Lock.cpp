#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti;
int n;
void work() {
    cin >> n;
    if ((n & 1) == 0) {
        cout << -1 << endl;
        return;
    }
    vector<int> ans;
    for (int i = 1; i <= n; i += 2) {
        ans.push_back(i);
    }
    for (int i = 2; i <= n; i += 2) ans.push_back(i);
    for (int x : ans) cout << x << ' ';
    cout << endl;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}