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
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
const int N = 2e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
const ld eps = 1e-6, PI = acosl(-1);
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
vi e[N];
using ull = unsigned long long;

void work() {
    cin >> n;
    vector<int> a(n), b(n);
    long long S = 0;
    rep(i, 0, n - 1) {
        cin >> a[i] >> b[i];
        S += 1LL * b[i] * b[i];
    }
    // 位集长度 = S+1, 按 64 位一块划分
    int M = S + 1;
    int B = (M + 63) >> 6;
    vector<ull> dp(B), ndp(B);
    dp[0] = 1;
    long long curMax = 0;

    rep(i, 0, n - 1) {
        fill(ndp.begin(), ndp.end(), 0ULL);
        int x = a[i], y = b[i];
        rep(j, x, y) {
            int d = j * j;
            int sb = d >> 6,  // 整块偏移
                fb = d & 63;  // 块内偏移
            long long newMax = curMax + d;
            int newB = min<long long>(B, (newMax >> 6) + 1);

            rep(bi, 0, (curMax >> 6)) {
                ull v = dp[bi];
                if (!v) continue;
                int to = bi + sb;
                if (to < newB) {
                    ndp[to] |= v << fb;
                    if (fb && to + 1 < newB) ndp[to + 1] |= v >> (64 - fb);
                }
            }
        }
        swap(dp, ndp);
        curMax = min<long long>(S, curMax + 1LL * y * y);
    }

    // 统计 0..curMax 中的 1
    long long ans = 0;
    int full = curMax >> 6, rem = curMax & 63;
    rep(i, 0, full - 1) ans += __builtin_popcountll(dp[i]);
    ull last = dp[full] & ((1ULL << (rem + 1)) - 1);
    ans += __builtin_popcountll(last);

    cout << ans << "\n";
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