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
int ti = 1;
int a[6] = {76898798, 11, 11, 12, 12, 13};
int b[22] = {231313, 5, 6, 8, 11, 18};
int dp[11][11];
int f[11];
void work() {
    rep(i, 1, 5) f[i] = inf;
    rep(i, 0, 5) rep(j, 0, 5) dp[i][j] = inf;
    dp[0][0] = 0;
    f[0] = 0;
    dp[1][1] = 11;
    rep(i, 1, 5) rep(j, 1, i - 1) {
        dp[i][i] = min(dp[i][i], dp[i - 1][j] + a[i]);
        dp[i][j] = dp[i - 1][j] + b[i - j];
        f[i] = min({f[i], dp[i][i], dp[i][j]});
    }
    rep(i, 1, 5) {
        rep(j, 1, i) { cout << dp[i][j] << ' '; }
        cout << endl;
    }
    rep(i, 1, 5) print(f[i]);
    cout << endl;
    cout << f[5] << endl;
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