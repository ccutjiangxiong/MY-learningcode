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

int ti = 1, n, m, k, a[N], b[N], c[N], ans, res, cnt, x, y, z;
vi e[N];

void work() {
    cin >> n >> m;
    struct Edge {
        int u, v, w, id;
    };
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }
    vi fa(n + 1);
    iota(fa.begin(), fa.end(), 0);
    function<int(int)> find = [&](int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); };
    auto unite = [&](int x, int y) { fa[find(x)] = find(y); };
    vector<bool> in_mst(m, false);
    vector<Edge> st = edges;
    sort(st.begin(), st.end(), [&](auto &a, auto &b) { return a.w < b.w; });
    int sum0 = 0;
    for (auto &e0 : st) {
        if (find(e0.u) != find(e0.v)) {
            unite(e0.u, e0.v);
            sum0 += e0.w;
            in_mst[e0.id] = true;
            e[e0.u].pb(e0.v), e[e0.v].pb(e0.u);
            a[e0.u] = max(a[e0.u], e0.w);
            b[e0.v] = max(b[e0.v], e0.w);
        }
    }
    vector<vii> g(n + 1);
    for (int i = 0; i < m; i++)
        if (in_mst[i]) {
            auto &e1 = edges[i];
            g[e1.u].emplace_back(e1.v, e1.w);
            g[e1.v].emplace_back(e1.u, e1.w);
        }
    int LOG = 20;
    vector<vi> up(n + 1, vi(LOG));
    vector<vi> ma1(n + 1, vi(LOG, -1)), ma2(n + 1, vi(LOG, -1));
    vi depth(n + 1);
    function<void(int, int)> dfs = [&](int u, int p) {
        for (auto &ed : g[u]) {
            int v = ed.first, w = ed.second;
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            up[v][0] = u;
            ma1[v][0] = w;
            ma2[v][0] = -1;
            dfs(v, u);
        }
    };
    dfs(1, 0);
    for (int j = 1; j < LOG; j++) {
        for (int v = 1; v <= n; v++) {
            int p = up[v][j - 1];
            up[v][j] = up[p][j - 1];
            int a1 = ma1[v][j - 1], a2 = ma1[p][j - 1];
            int b1 = ma2[v][j - 1], b2 = ma2[p][j - 1];
            vi ccs = {a1, a2, b1, b2};
            sort(ccs.begin(), ccs.end(), greater<int>());
            ma1[v][j] = ccs[0];
            ma2[v][j] = -1;
            for (int x : ccs)
                if (x < ma1[v][j]) {
                    ma2[v][j] = x;
                    break;
                }
        }
    }
    auto query = [&](int u, int v) {
        int mx1 = -1, mx2 = -1;
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int j = 0; j < LOG; j++)
            if (diff >> j & 1) {
                vi c = {mx1, mx2, ma1[u][j], ma2[u][j]};
                sort(c.begin(), c.end(), greater<int>());
                mx1 = c[0];
                mx2 = c[1];
                u = up[u][j];
            }
        if (u != v) {
            for (int j = LOG - 1; j >= 0; j--) {
                if (up[u][j] != up[v][j]) {
                    vi c = {mx1, mx2, ma1[u][j], ma2[u][j], ma1[v][j], ma2[v][j]};
                    sort(c.begin(), c.end(), greater<int>());
                    mx1 = c[0];
                    mx2 = c[1];
                    u = up[u][j];
                    v = up[v][j];
                }
            }
            for (int w : {ma1[u][0], ma1[v][0]}) {
                if (w > mx1)
                    mx2 = mx1, mx1 = w;
                else if (w > mx2)
                    mx2 = w;
            }
        }
        return pii(mx1, mx2);
    };
    vi cc;
    for (int i = 0; i < m; i++)
        if (!in_mst[i]) {
            auto &e2 = edges[i];
            auto [c1, c2] = query(e2.u, e2.v);
            if (c1 >= 0) cc.push_back(sum0 + e2.w - c1);
            if (c2 >= 0) cc.push_back(sum0 + e2.w - c2);
        }
    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    int s1 = sum0, s2 = -1, s3 = -1;
    int idx = 0;
    while (idx < sz(cc) && cc[idx] <= s1) idx++;
    if (idx < sz(cc)) s2 = cc[idx++];
    while (idx < sz(cc) && cc[idx] <= s2) idx++;
    if (idx < sz(cc)) s3 = cc[idx++];
    cout << s1 << " " << s2 << " " << s3 << "\n";
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