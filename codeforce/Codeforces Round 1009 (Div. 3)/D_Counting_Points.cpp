#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
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
int n, m;
int x[N], r[N];
void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> x[i];
    rep(i, 1, n) cin >> r[i];
    map<int, int> mp;
    rep(i, 1, n) {
        rep(j, x[i] - r[i], x[i] + r[i]) {
            int h = sqrt(r[i] * r[i] - (x[i] - j) * (x[i] - j));
            mp[j] = max(mp[j], 2 * h + 1);
        }
    }
    int ans = 0;
    for (auto [_, v] : mp) ans += v;
    cout << ans << endl;
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