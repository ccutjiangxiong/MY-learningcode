#include <bits/extc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rem(i, a, b) for (int i = (a); i >= (b); i--)
#define ran(l, r) uniform_int_distribution<decltype(l)>(l, r)(rng)
#define ranf(l, r) uniform_real_distribution<decltype(l)>(l, r)(rng)
#define lbt(a) __builtin_ctz(a)
#define cnt1(a) __builtin_popcount(a)
#define cnt0(a) __builtin_clz(a)
#define odd1(a) __builtin_parity(a)
#define all(a) a.begin(), a.end()
#define allp(a) a->begin(), a->end()
#define bitl(a) ((a) ? (64 - __builtin_clzll(a)) : 0)
#define sz(a) (int)a.size()
#define int long long
#define ld long double
#define se second
#define fi first
#define pb emplace_back
#define ep emplace
#define rg ranges
#define low lower_bound
#define upp upper_bound
#define con contains
#define me(a, x) memset(a, x, sizeof(a))
#define pta(x, a, b) rep(i, a, b) cout << x[i] << " \n"[i == b];
#define me1(x, n, ...) \
    for (auto *h : {__VA_ARGS__}) rep(i, 0, (n)) h[i] = x;
#define me2(x, n, m, ...) \
    for (auto h : {__VA_ARGS__}) rep(i, 0, (n)) rep(j, 0, (m)) h[i][j] = x;
#define fi1(x, n1, n2, ...) \
    for (auto *h : {__VA_ARGS__}) rep(i, (n1), (n2)) h[i] = x;
#define fl2(x, n1, n2, m1, m2, ...) \
    for (auto h : {__VA_ARGS__}) rep(i, (n1), (n2)) rep(j, (m1), (m2)) h[i][j] = x;
#define Ye(x) (x) ? "YES" : "NO"
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
template <typename Key, typename Mapped = null_type, typename Compare = std::less<Key>>
using ost = tree<Key, Mapped, Compare, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename Compare = std::greater<T>>
using hp = __gnu_pbds::priority_queue<T, Compare, pairing_heap_tag>;
template <typename Key, typename Mapped = null_type, typename Access = trie_string_access_traits<>>
using tri = trie<Key, Mapped, Access, pat_trie_tag, trie_prefix_search_node_update>;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using viii = vector<piii>;
using ill = __int128;
using ull = unsigned long long;
using ll = long long;
using cpx = complex<ld>;
using u32 = uint32_t;
using u128 = unsigned __int128;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
void be(vii edges[N]) {
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
int f1[N], f2[N], g1[N], g2[N];
vii e[N];
int dp[110][(1 << 10)], tr[N];
int dis[N], cnt[N], vis[N];
std::priority_queue<pii, vector<pii>, greater<>> pq;
void dij(int s) {
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dp[u][s]) continue;
        for (auto [v, w] : e[u]) {
            ll nd = d + w;
            if (dp[v][s] > nd) {
                dp[v][s] = nd;
                pq.emplace(nd, v);
            }
        }
    }
}
…
    // clear the old fun() and work() and paste this in:

    // 1) DP + Dijkstra over all subsets of the k terminals
    void
    fun() {
    int FULL = 1 << k;
    for (int s = 1; s < FULL; s++) {
        // subset‐DP merge step
        for (int u = 1; u <= n * m; u++) {
            for (int su = (s - 1) & s; su; su = (su - 1) & s) {
                dp[u][s] = min(dp[u][s], dp[u][su] + dp[u][s ^ su]);
            }
            if (dp[u][s] < inf) pq.emplace(dp[u][s], u);
        }
        dij(s);
    }
}

// 2) read, build graph, init DP, call fun(), find answer, print
void work() {
    cin >> n >> m;
    // reset
    k = 0;
    for (int i = 1; i <= n * m; i++) {
        e[i].clear();
        for (int s = 0; s < (1 << 10); s++) dp[i][s] = inf;
    }
    // read grid, mark terminals (a[id]==0)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int v;
            cin >> v;
            int id = (i - 1) * m + j;
            a[id] = v;
            if (v == 0) {
                dp[id][1 << k] = 0;  // terminal mask
                k++;
            }
        }
    }
    // build 4‐neigh graph: cost to enter v is a[v]
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int u = (i - 1) * m + j;
            if (i > 1) {
                int v = u - m;
                e[u].pb(v, a[v]);
            }
            if (i < n) {
                int v = u + m;
                e[u].pb(v, a[v]);
            }
            if (j > 1) {
                int v = u - 1;
                e[u].pb(v, a[v]);
            }
            if (j < m) {
                int v = u + 1;
                e[u].pb(v, a[v]);
            }
        }
    }
    // run the Steiner‐DP
    fun();
    int FULL = (1 << k) - 1;
    // find best end‐node
    ll best = inf;
    int bk = 1;
    for (int u = 1; u <= n * m; u++) {
        if (dp[u][FULL] < best) {
            best = dp[u][FULL];
            bk = u;
        }
    }
    // TODO: backtrack from (bk, FULL) to mark which nodes are used
    // e.g. a dfs/stack using a 'pre[u][s]' or similar
    vector<char> used(n * m + 1, 0);
    // mark your used[...] = 1 ...

    // output
    cout << best << "\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int id = (i - 1) * m + j;
            if (a[id] == 0)
                cout << 'x';
            else if (used[id])
                cout << 'o';
            else
                cout << '_';
        }
        cout << "\n";
    }
}
// rest of main() unchanged

// … 后面 main 保持不变 …

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) {
        work();
    }
    return 0;
}