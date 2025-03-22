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
int n;
int a[N];
int dp[888][888];
int solve(int l, int r) {
    if (l + 2 > r) return 0;
    if (dp[l][r]) return dp[l][r];
    int ans = 0;
    rep(i, l + 1, r - 1) ans =
        max(ans, solve(l + 1, i - 1) + solve(i + 1, r - 1) + a[l] * a[i] * a[r]);
    rep(i, l, r - 1) ans = max(ans, solve(l, i) + solve(i + 1, r));
    return dp[l][r] = ans;
}
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) a[i + n] = a[i];
    rep(i, 1, n * 2) rep(j, 1, 2 * n) dp[i][j] = 0;
    int ans = 0;
    solve(1, 2 * n);
    rep(i, 1, n) ans = max(ans, dp[i][i + n - 1]);
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