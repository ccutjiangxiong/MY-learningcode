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
const int N = 2e5 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int ti, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vii e[N];
int dis[2][N], vis[N];
void dijm(int s, int mo) {
    priority_queue<pii, vii, greater<>> pq;
    // me(dis[mo], 0x3f);
    // me(vis, 0);
    rep(i, 1, n) dis[mo][i] = inf, vis[i] = 0;
    pq.ep(dis[mo][s] = 0, s);
    while (pq.size()) {
        int u = pq.top().se;
        pq.pop();
        if (vis[u]++) continue;
        for (auto [v, w] : e[u]) {
            int t = max(w, dis[mo][u]);
            if (t < dis[mo][v]) pq.ep(dis[mo][v] = t, v);
        }
    }
}
void work() {
    cin >> n >> m;
    viii ed;
    rep(i, 1, n) e[i].clear();
    me(dis, 0);
    rep(i, 1, m) {
        cin >> x >> y >> z;
        ed.pb(x, y, z);
        e[x].pb(y, z);
        e[y].pb(x, z);
    }
    dijm(1, 0);
    dijm(n, 1);
    ans = inf;
    for (auto [u, v, w] : ed) {
        ans = min(ans, w + max({dis[0][u], dis[1][v], w}));
        ans = min(ans, w + max({dis[0][v], dis[1][u], w}));
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