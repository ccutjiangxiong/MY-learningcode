#include <bits/stdc++.h>
#define int long long
#define ld long double
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define vi vector<int>
#define pb emplace_back
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using namespace std;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using ill = __int128;
using namespace numbers;
void be(int u, int v, auto e[N]) {
    cin >> u >> v;
    e[u].pb(v), e[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1;
int dp[101][101][101];
void work() {
    int n, x, y;
    cin >> n >> x >> y;
    me(dp, -0x3f);
    dp[0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        vector<int> f(c + 1), g(c + 1);
        rep(j, 1, c) cin >> f[j];
        rep(j, 1, c) cin >> g[j];
        rep(h, 0, 100) rep(w, 0, 100) {
            if (dp[i][h][w] < 0) continue;
            rep(j, 1, c) if (w + g[j] < 100) dp[i + 1][h][w + g[j]] =
                max(dp[i + 1][h][w + g[j]], dp[i][h][w] + f[j]);
            if (h + 1 < 100) dp[i + 1][h + 1][w] = max(dp[i + 1][h + 1][w], dp[i][h][w]);
            if (w + y < 100) dp[i + 1][h][w + y] = max(dp[i + 1][h][w + y], dp[i][h][w] + x);
        }
    }
    int ans = 0;
    rep(h, 0, 100) for (int w = 0; w <= h && w < 100; w++) ans = max(ans, dp[n][h][w]);
    cout << ans << "\n";
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