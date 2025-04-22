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
random_device rd;
mt19937 rnd(rd());
inline int rand(int l, int r) { return uniform_int_distribution<int>(l, r)(rnd); }
void be(auto edges[N]) {
    int u, v;
    cin >> u >> v;
    edges[u].pb(v), edges[v].pb(u);
}

template <typename... T>
void print(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti;
int x, y;
int vis[N];
int ans = 0;
int dp[222][222];
void work() {
    cin >> x >> y;

    int f = 1;
    int ans = inf;
    rep(i, 0, 63) rep(j, 0, 63) {
        if ((x >> i) == (y >> j) && (f)) {
            ans = min(ans, dp[i][j]);
        }
    }
    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    me(dp, 0x3f);
    dp[0][0] = 0;
    rep(k, 1, 60) rem(i, 60, 0) rem(j, 60, 0) {
        dp[i + k][j] = min(dp[i + k][j], dp[i][j] + (1ll << k));
        dp[i][j + k] = min(dp[i][j + k], dp[i][j] + (1ll << k));
    }
    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}