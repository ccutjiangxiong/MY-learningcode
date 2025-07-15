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
    int u, v, w;
    cin >> u >> v >> w;
    edges[u].pb(v, w), edges[v].pb(u, w);
}

template <typename... T>
void pt(T... a) {
    ((cout << a << ' '), ...);
    cout << "\n";
}

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;

vii ee[N];
vii h;
int d[12][N];
int dis[N], vis[N];
void dij(int s) {
    rep(i, 1, n) dis[i] = inf, vis[i] = 0;
    priority_queue<pii, vii, greater<>> pq;
    rep(j, 1, a[s]) d[j][s] = 0;
    pq.ep(dis[s] = 0, s);
    while (pq.size()) {
        int u = pq.top().se;
        pq.pop();
        if (vis[u]++) continue;
        ans++;
        for (auto [v, w] : ee[u]) {
            if (dis[u] + w < dis[v] && dis[u] + w < d[a[s] + 1][v]) {
                pq.ep(dis[v] = dis[u] + w, v);
                d[a[s]][v] = min(dis[v], d[a[s]][v]);
                rep(j, 1, a[s]) d[j][v] = min(d[j][v], dis[v]);
            }
        }
    }
}
void work() {
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i], h.pb(a[i], i);
    rep(i, 1, m) be(ee);
    rep(i, 1, n) rep(j, 1, 11) d[j][i] = inf;
    rg::sort(h, greater<>());
    for (auto [r, id] : h) dij(id);

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