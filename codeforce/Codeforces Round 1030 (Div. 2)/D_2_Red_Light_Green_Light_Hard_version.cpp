#include <bits/extc++.h>

#include <unordered_map>

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

int ti, n, m, k, a[N], b[N], c[N], ans, res, tot, x, y, z;
int f[2][N], g1[N], g2[N];
struct Hsh {
    ull operator()(const ull &x) const {
        static const ull r = rng();
        return x ^ r;
    }
};
unordered_map<int, int, Hsh> mp[2];
int vis[2][N];
bool dfs(int u, int dir) {
    if (mp[dir][u]) return mp[dir][u];
    if (u == 0) return mp[dir][u] = true;
    if (vis[dir][u]++) return mp[dir][u] = false;
    return mp[dir][u] = dfs(f[dir][u], dir ^ 1);
}
void work() {
    cin >> n >> k;
    unordered_map<int, int, Hsh> mp1, mp2, mp3;
    for (int *h : {a, b}) rep(i, 1, n) cin >> h[i];
    me1(0, n, c);
    me2(0, 1, n, vis, f);
    rep(i, 0, 1) mp[i].clear();
    rep(i, 1, n) {
        int x = (a[i] + b[i]) % k;
        if (mp1.con(x)) f[0][i] = mp1[x];
        mp1[x] = i;
    }
    rem(i, n, 1) {
        int x = (a[i] - b[i] + k) % k;
        if (mp2.con(x)) f[1][i] = mp2[x];
        mp2[x] = i;
    }
    cin >> m;
    vii g;
    rep(i, 1, m) g.pb((cin >> x, x), i);
    rg::sort(g);
    int cnt = n;
    rem(i, m, 1) {
        auto [x, id] = g[i - 1];
        while (cnt && a[cnt] >= x) mp3[(a[cnt] - b[cnt] + k) % k] = cnt, cnt--;
        c[id] = (!mp3.con(x % k) ? 1 : dfs(mp3[x % k], 0));
    }
    rep(i, 1, m) pt(Ye(c[i]));
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