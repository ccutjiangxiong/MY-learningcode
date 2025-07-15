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

int ti, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
struct E {
    int v, w, id, d;
};
vector<E> e[N];
int f[N],cd[N][2],g[N],dep[N];
void dfs1(int u, int fa) {
    f[u] = a[u];
    for (auto [v, w, id, d] : e[u])
        if (v != fa) {
            dfs1(v, u);
            int c = max(0ll, f[v] - 2 * w);
            cd[id][d] = c;
            f[u]+=c;
    }
}

void dfs2(int u, int fa) {
    int s = g[u];
    for(auto v:e[u]) s+=cd[v.id][v.d];
    for (auto [v, w, id, d] : e[u])
        if (v != fa) {
            int c1 = cd[id][d];
            int ex = a[u] + (s - c1);
            int cu = max(0ll, ex - 2 * w);
            cd[id][d ^ 1] = g[v] = cu;
            dfs2(v,u);
    }
}
void dfs3(int u, int p) {
    for (auto [v, w, id, d] : e[u]) {
        dep[]
    }
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i], e[i].clear();
    rep(i, 1, n - 1) {
        cin >> x >> y >> z;
        e[x].pb(y, z, i, 0);
        e[y].pb(x, z, i, 1);
    }
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