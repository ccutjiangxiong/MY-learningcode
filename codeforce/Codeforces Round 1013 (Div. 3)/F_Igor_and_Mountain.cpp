#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5, mod = 998244353, inf = 1e18 + 3;
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
int n, m, k;
char mat[2222][2222];
int dp[2222][2222], pre[2222][2222];
void work() {
    cin >> n >> m >> k;
    rep(i, 1, n) rep(j, 1, m) cin >> mat[i][j];
    rep(i, 1, n) rep(j, 1, m) dp[i][j] = 0;
    rep(i, 1, m) if (mat[1][i] == 'X') dp[1][i] = 1;
    rep(i, 1, m) pre[1][i] = pre[1][i - 1] + dp[1][i];
    rep(i, 1, m) if (mat[1][i] ==
                     'X')(dp[1][i] = pre[1][min(m, i + k)] - pre[1][max(1ll, i - k) - 1]) %= mod;
    rep(i, 1, m)(pre[1][i] = pre[1][i - 1] + dp[1][i]) %= mod;
    rep(i, 2, n) {
        rep(j, 1, m) if (mat[i][j] == 'X')(dp[i][j] = pre[i - 1][min(m, j + k - 1)] -
                                                      pre[i - 1][max(1ll, j - k + 1) - 1]+mod) %= mod;
        rep(j, 1, m)(pre[i][j] = (pre[i][j - 1] + dp[i][j])) %= mod;
        rep(j, 1, m) if (mat[i][j] == 'X')(dp[i][j] = pre[i][min(m, j + k)] -
                                                      pre[i][max(1ll, j - k) - 1]+mod) %= mod;
        rep(j, 1, m)(pre[i][j] = (pre[i][j - 1] + dp[i][j])) %= mod;
    }
    cout << pre[n][m] << endl;
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