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
bitset<10> s1,s2;
void fun() {
    rep(s, 1, (1 << k) - 1) {
        rep(i, 1, n) {
            pt(s, "---------------------------");
            for (int su = s & (s - 1); su; su = s & (su - 1))
                dp[i][s] = min(dp[i][s], dp[i][su] + dp[i][s ^ su]), s1=s,s2=su,pt(s1,s2);
            if (dp[i][s] < 1e9) pq.emplace(dp[i][s], i);
        }
        dij(s);
    }
}
void work() {
    me(dp, 0x3f);
    cin >> n >> m >> k;
    rep(i, 1, m) be(e);
    rep(i, 0, k - 1) {
        cin >> b[i];
        dp[b[i]][1 << i] = 0;
    }
    fun();
    ll ans = inf;
    int full = (1 << k) - 1;
    rep(i, 1, n) ans = min(ans, dp[b[0]][full]);
    cout << ans << "\n";
}

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