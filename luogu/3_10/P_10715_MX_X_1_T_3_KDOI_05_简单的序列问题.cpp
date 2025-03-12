#include <bits/stdc++.h>
// #define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti;
int n;
int a[N], c[N];
vector<int> g, f;
int ans[N];
int dp[501][501][501];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) cin >> c[i];
    rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) dp[i][j][k] = mod;
    int s = 0;
    dp[0][0][0] = 0;
    rep(i, 1, n) a[i] %= 2, s += a[i];
    rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) {
        dp[i + 1][j][k + j % 2] =
            min(dp[i + 1][j][k + j % 2], dp[i][j][k] + (a[i + 1] == 0 ? 0 : c[i + 1]));
        dp[i + 1][j + 1][k + (j+1) % 2] =
            min(dp[i + 1][j + 1][k + (j+1) % 2], dp[i][j][k] + (a[i + 1] == 1 ? 0 : c[i + 1]));
    }

    rep(i, 0, n) if (dp[n][s][i] == mod) cout << -1 << ' ';
    else cout << dp[n][s][i] << ' ';
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