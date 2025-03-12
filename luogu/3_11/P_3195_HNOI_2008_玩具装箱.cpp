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
int n, l;
int f[N], dp[N], pre[N];
int x[N], y[N];
int q[N], cnt, st = 1;
int fun(int x) { return x * x; }

double slope(int u, int v) { return x[u] == x[v] ? 0 : (y[u] - y[v]) * 1.0 / (x[u] - x[v]); }
void work() {
    cin >> n >> l;
    rep(i, 1, n) cin >> f[i];
    rep(i, 1, n) f[i]++;
    rep(i, 1, n) dp[i] = inf, pre[i] = pre[i - 1] + f[i];
    l++;
    dp[0] = 0;
    q[++cnt] = 0;
    rep(i, 1, n) {
        // rep(j, st, cnt) dp[i] = min(dp[i], dp[q[j]] + fun(pre[i] - pre[q[j]] - l));
        while (cnt - st >= 1 && slope(q[st], q[st + 1]) < 2 * pre[i]) st++;
        dp[i] = min(dp[i], dp[q[st]] + fun(pre[i] - pre[q[st]] - l));
        y[i] = dp[i] + 2 * pre[i] * l + pre[i] * pre[i];
        x[i] = pre[i];
        while (cnt - st >= 1 && slope(i, q[cnt - 1]) <= slope(q[cnt - 1], q[cnt])) cnt--;
        q[++cnt] = i;
    }
    // print(cnt - st);
    // print(slope(2, 3));
    // rep(i, 1, n) print(dp[i]);
    cout << dp[n];
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