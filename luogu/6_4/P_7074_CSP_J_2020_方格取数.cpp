#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
#define all(a) a.begin(), a.end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define sz(a) (int)a.size()
using namespace std;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define me(a, x) memset(a, x, sizeof(a))
const int N = 2e3 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = uint64_t;

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

int ti = 1, n, m, k, a[N][N], b[N][N], c[N], ans, res, cnt, x, y, z;
vi e[N];
int pre[N], suf[N], dp[N][N];
void work() {
    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
    rep(j, 1, m) rep(i, 1, n) b[j][i] = b[j][i - 1] + a[i][j];
    pre[0] = suf[n + 1] = -1e17;
    fill(dp[1] + 2, dp[1] + 1 + n, -inf);
    dp[1][1] = a[1][1];
    rep(i, 2, m + 1) {  // 按列进行转移
        // 预处理pre和suf数组
        rep(j, 1, n) pre[j] = max(pre[j - 1], dp[i - 1][j] - b[i - 1][j]);
        rem(j, n, 1) suf[j] = max(suf[j + 1], dp[i - 1][j] + b[i - 1][j - 1]);
        rep(j, 1, n) dp[i][j] = max(pre[j] + b[i - 1][j], suf[j] - b[i - 1][j - 1]) + a[j][i];
    }
    print(dp[m + 1][n]);
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