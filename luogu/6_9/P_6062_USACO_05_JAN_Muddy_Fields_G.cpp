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
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
vi e[N];
char gr[222][222], vis[222][222];
int rd[222][222], cd[222][222];
vi g, f;
bool dfs(int u) {
    for (int v : e[u])
        if (!b[v]++ && (!c[v] || (dfs(c[v])))) return (c[v] = u, 1);
    return 0;
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, m) cin >> gr[i][j];
    int rt = 0, ct = 0;
    rep(i, 1, n) rep(j, 1, m) rd[i][j] = (rt += (gr[i][j] == '.' || j == 1));
    rep(j, 1, m) rep(i, 1, n) cd[i][j] = (ct += (gr[i][j] == '.' || i == 1));
    rep(i, 1, n) rep(j, 1, m) if (gr[i][j] == '*') e[rd[i][j]].pb(cd[i][j]);
    rep(i, 1, rt) {
        rep(j, 0, ct) b[j] = 0;
        ans += dfs(i);
    }
    pt(ans);
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