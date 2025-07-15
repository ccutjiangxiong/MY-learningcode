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
    for (auto* h : {__VA_ARGS__}) rep(i, 0, (n)) h[i] = x;
#define me2(x, n, m, ...) \
    for (auto h : {__VA_ARGS__}) rep(i, 0, (n)) rep(j, 0, (m)) h[i][j] = x;
#define fi1(x, n1, n2, ...) \
    for (auto* h : {__VA_ARGS__}) rep(i, (n1), (n2)) h[i] = x;
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
using i32 = int32_t;
static u32 Mod, inv, r2;
struct Mont {
    u32 v;
    static void init(u32 mod) {
        Mod = mod, inv = 1;
        for (int i = 0; i < 5; ++i) inv *= 2u - inv * Mod;
        inv = -inv;
        u64 t = (u64(1) << 32) % Mod;
        r2 = u32(t * t % Mod);
    }
    static u32 reduce(u64 t) {
        u32 y = (t + u64(u32(t) * inv) * Mod) >> 32;
        return i32(y) < 0 ? y + Mod : y;
    }
    Mont() : v(0) {}
    Mont(int x) : v(reduce(u64(x) * r2)) {}
    static Mont pow(Mont a, ll e) {
        Mont res(1);
        while (e) {
            if (e & 1) res *= a;
            a *= a, e >>= 1;
        }
        return res;
    }
    static Mont invMont(const Mont& a) { return pow(a, (ll)Mod - 2); }
    Mont& operator+=(const Mont& o) { return (v + o.v, v = v >= Mod ? v - Mod : v), *this; }
    Mont& operator-=(const Mont& o) { return (v = v < o.v ? v + Mod : v, v -= o.v), *this; }
    Mont& operator*=(const Mont& o) { return v = reduce(u64(v) * o.v), *this; }
    Mont& operator/=(const Mont& o) { return *this *= invMont(o); }
    friend constexpr auto operator+(Mont a, const auto& b) noexcept { return a += b; }
    friend constexpr auto operator-(Mont a, const auto& b) noexcept { return a -= b; }
    friend constexpr auto operator*(Mont a, const auto& b) noexcept { return a *= b; }
    friend constexpr auto operator/(Mont a, const auto& b) noexcept { return a /= b; }
    int get() const {
        u32 x = reduce(v);
        return x >= m ? x - m : x;
    }
};

void work() {
    u32 m;
    cin >> n >> m;
    Mont::init(m);
    mint res = 1;
    rep(i, 1, n) res += (i ^ 1), res *= i;
    pt(res);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (ti == 0) cin >> ti;
    while (ti--) work();
    return 0;
}
