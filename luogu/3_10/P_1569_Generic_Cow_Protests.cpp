#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
const int N = 2e6 + 5;
const int mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}
int ti = 1;
int n;
int g[N];
int dp[1111][1111];
int pre[N], ans[N];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> g[i];
    rep(i, 1, n) pre[i] = pre[i - 1] + g[i];
    ans[1] = 1;
    rep(i, 1, n) rep(j, i, n) {
        if (pre[j] - pre[i - 1] >= 0 && ans[i - 1]) dp[i][j] = ans[i - 1] + 1;
        ans[j] = max(ans[j], dp[i][j]);
    }
    // rep(i, 1, n) cout << ans[i] << endl;
    if (ans[n])
        cout << ans[n];
    else
        cout << "Impossible";
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