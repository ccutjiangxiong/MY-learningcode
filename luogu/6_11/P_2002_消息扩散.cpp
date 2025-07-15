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
void dfs(int x) {
    for (int v : e[x])
        if (!b[v]++) dfs(v);
}
vi g;
// …existing code…
void work() {
    cin >> n >> m;
    // clear graph
    rep(i, 1, n) { e[i].clear(); }
    // read directed edges
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        e[u].pb(v);
    }

    // prepare Tarjan
    static int dfn[N], low[N], scc_id[N], stk[N];
    static bool in_stk[N];
    int dfc = 0, scc_cnt = 0, top = 0;
    // reset per-test
    rep(i, 1, n) {
        dfn[i] = low[i] = 0;
        in_stk[i] = false;
    }

    function<void(int)> tarjan = [&](int u) {
        dfn[u] = low[u] = ++dfc;
        stk[++top] = u;
        in_stk[u] = true;
        for (int v : e[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            scc_cnt++;
            int x;
            do {
                x = stk[top--];
                in_stk[x] = false;
                scc_id[x] = scc_cnt;
            } while (x != u);
        }
    };

    // run Tarjan over all nodes
    rep(i, 1, n) if (!dfn[i]) tarjan(i);

    // build indegree of condensed DAG
    vector<int> indeg(scc_cnt + 1, 0);
    rep(u, 1, n) {
        for (int v : e[u]) {
            if (scc_id[u] != scc_id[v]) {
                indeg[scc_id[v]]++;
            }
        }
    }
    // count how many SCCs have indegree==0
    int ans = 0;
    rep(i, 1, scc_cnt) {
        if (indeg[i] == 0) ans++;
    }

    pt(ans);
}
// …existing code…

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}