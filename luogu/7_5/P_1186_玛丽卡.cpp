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
using ll = int64_t;
using cpx = complex<ld>;
const int N = 1005, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
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
int f1[N], f2[N], g1[N], g2[N];
vector<piii> e[N];
int dis[N], cnt[N], vis[N], la[N], le[N];
void dij(int s) {
    std::priority_queue<pii, vector<pii>, greater<>> pq;
    me(dis, 0x3f);
    me(vis, 0);
    me(la, 0);
    me(le, 0);
    dis[s] = 0;
    pq.ep(0, s);
    while (pq.size()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]++) continue;
        for (auto [v, w, id] : e[u]) {
            if (dis[u] + w < dis[v]) pq.emplace(dis[v] = dis[u] + w, v), la[v] = id, le[v] = u;
        }
    }
}
struct Hsh {
    ull operator()(const ull &x) const {
        static const ull r = rng();
        return x ^ r;
    }
};
auto Time() { return (1.0 * clock() / CLOCKS_PER_SEC); }
void work() {
    cin >> n >> m;
    viii h;
    rep(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        h.pb(u, v, w);
        e[u].pb(v, w, i);
        e[v].pb(u, w, i);
    }
    set<int> g;
    dij(1);
    rep(i, 1, n) a[i] = dis[i];
    dij(n);
    rep(i, 1, n) b[i] = dis[i];
    int p = n;
    while (p) {
        g.ep(la[p]);
        p = le[p];
    }
    int ans = inf, res = inf;
    rep(i, 1, m) {
        auto [u, v, w] = h[i - 1];
        if (!g.con(i)) {
            if (a[u] < inf && b[v] < inf) ans = min(ans, a[u] + b[v] + w);
            if (a[v] < inf && b[u] < inf) ans = min(ans, a[v] + b[u] + w);
        }
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