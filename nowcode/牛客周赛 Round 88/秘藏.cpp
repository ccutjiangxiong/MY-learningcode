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
int n, k;
int a[N], b[N];
int dp[N][2];
void work() {
    cin >> n >> k;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) cin >> b[i];
    dp[0][0]  = -inf;
    rep(i, 1, n) {
        dp[i][1] = max(dp[i - 1][1] + a[i], dp[i - 1][0] >= k ? dp[i - 1][0] - k + a[i] : -inf);
        dp[i][0] = max(dp[i - 1][0] + b[i], dp[i - 1][1] >= k ? dp[i - 1][1] - k + b[i] : -inf);
    }
    cout << max(dp[n][0], dp[n][1]) << endl;
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