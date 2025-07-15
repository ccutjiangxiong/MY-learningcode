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
using ull = uint64_t;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const double eps = 1e-6;
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
int f1[N], f2[N], g1[N], g2[N];
vii e[N];
// vii e[N];
int g[N], d[N], cur[N], f[N];
int s, t, cnt = 0;
void add(int u, int v, int c, int id = 0) {
    int x = cnt++, y = cnt++;
    e[u].pb(v, x);
    e[v].pb(u, y);
    g[x] = c, g[y] = 0, f[id] = x;
}
bool bfs(int s, int t) {
    rep(i, s, t) d[i] = inf;
    queue<int> q;
    q.push(s);
    d[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : e[u]) {
            if (g[w] && d[v] == inf) {
                q.push(v);
                d[v] = d[u] + 1;
                if (v == t) return true;
            }
        }
    }
    return false;
}
int dfs(int u, int flow, int t) {
    if (u == t) return flow;
    int sum = 0;
    for (int &i = cur[u]; i < e[u].size(); i++) {
        auto [v, w] = e[u][i];
        if (d[v] == d[u] + 1 && g[w]) {
            int f = min(flow, g[w]);
            int re = dfs(v, f, t);
            g[w] -= re, g[w ^ 1] += re;
            sum += re, flow -= re;
            if (flow == 0) break;
        }
    }
    if (sum == 0) d[u] = 0;
    return sum;
}
int dinic(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
        ans += dfs(s, inf, t);
        me(cur, 0);
    }
    return ans;
}
void work() {
    cin >> n >> m;
    x = 1111;
    rep(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w * x + 1);
    }

    int ans = dinic(1, n);
    pt(ans / x, ans % x);
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