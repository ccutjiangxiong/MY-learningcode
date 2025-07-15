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

void work() {
    cin >> n;
    static int pos[N];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    // build prefix sums S1[i]=sum_{1..i} i, S2[i]=sum_{1..i} i^2, P2[i]=sum_{j=1..i} S2[j]
    static ll S1[N], S2[N], P2[N];
    S1[0] = S2[0] = P2[0] = 0;
    for (int i = 1; i <= n; i++) {
        S1[i] = (S1[i - 1] + i) % mod;
        S2[i] = (S2[i - 1] + (ll)i * i) % mod;
        P2[i] = (P2[i - 1] + S2[i]) % mod;
    }
    auto range_sum = [&](ll *P, int l, int r) {
        if (l > r) return 0LL;
        ll v = (P[r] - P[l - 1]) % mod;
        if (v < 0) v += mod;
        return v;
    };
    // calc sum_{l=a..b, r=c..d} (r-l+1)^2 mod
    auto calc = [&](int a, int b, int c, int d) {
        if (a > b || c > d) return 0LL;
        ll cntL = b - a + 1, cntR = d - c + 1;
        ll sumL = range_sum(S1, a, b), sumL2 = range_sum(S2, a, b);
        ll sumR = range_sum(S1, c, d), sumR2 = range_sum(S2, c, d);
        ll t1 = sumR2 * cntL % mod;
        ll t2 = 2 * sumR % mod * cntL % mod;
        ll t3 = cntL % mod * cntR % mod;
        ll t4 = sumL2 * cntR % mod;
        ll t5 = (mod - 2 * (sumR * sumL % mod)) % mod;
        ll t6 = (mod - 2 * sumL % mod * cntR % mod) % mod;
        ll ans = (t1 + t2 + t3 + t4 + t5 + t6) % mod;
        return ans;
    };
    ll ans = 0;
    // k = 1
    int p1 = pos[1];
    ans = (ans + P2[p1 - 1] + P2[n - p1]) % mod;
    // now maintain current [L,R] = range of positions of {1..k-1}
    int L = p1, R = p1;
    for (int k = 2; k <= n; k++) {
        int pk = pos[k];
        ll sumk = 0;
        // case1: pk < L  => l∈[pk+1..L], r∈[R..n]
        if (pk < L) {
            sumk = (sumk + calc(pk + 1, L, R, n)) % mod;
        }
        // case2: pk > R  => l∈[1..L], r∈[R..pk-1]
        if (pk > R) {
            sumk = (sumk + calc(1, L, R, pk - 1)) % mod;
        }
        L = min(L, pk);
        R = max(R, pk);
        ll kk = (ll)k * k % mod;
        ans = (ans + kk * sumk) % mod;
    }
 
    ll t = (ll)n * (n + 1) % mod;
    ans = (ans + t * t % mod) % mod;
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