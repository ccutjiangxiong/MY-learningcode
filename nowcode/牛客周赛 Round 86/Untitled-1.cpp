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
int a[N];
int dp[3333][3333];
int ans[N];
int pre[N];
int su1[N], su2[N];
void work() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) pre[i] = pre[i - 1] + a[i];
    rep(i, 1, n) rep(j, 1, n) dp[i][j] = 0;
    rep(i, 1, n) ans[i] = 0;
    su1[0] = inf;
    rep(i, 1, n) su1[i] = min(su1[i - 1], a[i]);
    su2[n + 1] = inf;
    rem(i, n, 1) su2[i] = min(su2[i + 1], a[i]);

    rep(i, 1, n) rep(j, 1, i) ans[i - j] =
        max(ans[i - j], abs(pre[i] - pre[j - 1] - min(su2[i + 1], su1[j - 1])));
    ans[n - 1] = 0;
    rep(i, 0, n - 1) cout << ans[i] << ' ';
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