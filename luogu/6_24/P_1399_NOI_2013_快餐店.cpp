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
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
map<pii, int> mp;
void be(auto edges[N]) {
    int u, v, w;
    cin >> u >> v >> w;
    mp[{u, v}] = mp[{v, u}] = w;
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
deque<int> st;
set<int> ss;
int vis[N];
bool dfs1(int u, int fa) {
    if (vis[u]++) {
        while (st.front() != u) st.pop_front();
        return true;
    }
    st.pb(u);
    for (auto [v, w] : e[u])
        if ((v != fa) && dfs1(v, u)) return true;
    return false;
}
int dep[N];
int dfs2(int u, int fa) {
    int de = 0;
    for (auto [v, w] : e[u])
        if (v != fa && !ss.con(v)) {
            int l = dfs2(v, u) + w;
            ans = max(ans, l + de);
            de = max(de, l);
        }
    return de;
}
void work() {
    cin >> n;
    rep(i, 1, n) be(e);
    dfs1(1, 0);
    for (int x : st) ss.ep(x);
    for (int x : st) dep[x] = dfs2(x, 0);
    vi g;
    for (int x : st) g.pb(x);
    for (int x : st) g.pb(x);
    set<pii> ts, ts2;
    int m = sz(g);
    vi pre(m + 1);
    rep(i, 1, m - 1) pre[i] = pre[i - 1] + mp[{g[i], g[i - 1]}];
    rep(i, 0, (m / 2) - 1) {
        ts.ep(dep[g[i]] - pre[i],g[i]);
        ts2.ep(dep[g[i]] + pre[i],g[i]);
    };
    res = inf;
    rep(i, (m / 2), m - 1) {
        // 取 ts 和 ts2 的前两大元素
        auto it1 = prev(ts.end());
        auto it1_sec = ts.size() > 1 ? prev(it1) : it1;
        auto it2 = prev(ts2.end());
        auto it2_sec = ts2.size() > 1 ? prev(it2) : it2;
        // 如果它们对应的 g[i] 相同，取次大组合
        long long best = inf;
        if (it1->second != it2->second) {
            best = it1->first + it2->first;
        } else {
            best = min(it1_sec->first + it2->first, it1->first + it2_sec->first);
        }
        res = min(res, best);
        // 删除滑出窗口的那一对，加入新的
        int j = i - (m / 2);
        ts.erase(ts.find(make_pair(dep[g[j]] - pre[j], g[j])));
        ts2.erase(ts2.find(make_pair(dep[g[j]] + pre[j], g[j])));
        ts.emplace(dep[g[i]] - pre[i], g[i]);
        ts2.emplace(dep[g[i]] + pre[i], g[i]);
    }
    // pt(ans);
    ans = max(ans, res);
    cout << format("{:.1f}", ans * 0.5);
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