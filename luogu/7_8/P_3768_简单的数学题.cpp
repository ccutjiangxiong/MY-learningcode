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
using u64 = uint64_t;
using ll = int64_t;
using u32 = uint32_t;
using cpx = complex<ld>;
const int N = 1e6 + 5, mod = 1e9 + 7, inf = 1e18 + 3;
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

int ti = 1, n, m, k, a[N], ans, res, tot, x, y, z;
vi e[N];
int pri[N], phi[N], mu[N], cnt = 0;
bitset<N> isp;
void euler(int n) {
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!isp[i]) pri[++cnt] = i, phi[i] = i - 1, mu[i] = -1;
        for (int j = 1; j <= cnt && i * pri[j] <= n; j++) {
            isp[i * pri[j]] = 1;
            phi[i * pri[j]] = phi[i] * (pri[j] - (i % pri[j] != 0));
            // mu[i * pri[j]] = i % pri[j] ? -mu[i] : 0;
            if (i % pri[j] == 0) break;
        }
    }
}
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ill)a * ans % p;
        a = (ill)a * a % p;
        b >>= 1;
    }
    return ans;
}
// p为质数
int invp(int a, int p) { return qpow(a, p - 2, p); }
using u128 = unsigned __int128;
static u64 Mod, inv, r2;
struct Mont {
    u64 v;
    static void init(u64 m) {
        Mod = m, inv = 1;
        rep(i, 1, 6) inv *= 2 - inv * Mod;
        u128 t = (u128(1) << 64) % Mod;
        inv = -inv, r2 = (u64)(t * t % Mod);
    }
    static u64 reduce(u128 t) {
        u64 m = (u64)t * inv;
        u64 u = (u64)((t + (u128)m * Mod) >> 64);
        return u >= Mod ? u - Mod : u;
    }
    Mont() : v(0) {}
    Mont(u64 x) : v(reduce((u128)x * r2)) {}
    static Mont pow(Mont a, ll e) {
        Mont res((u64)1);
        while (e) {
            if (e & 1) res *= a;
            a *= a, e >>= 1;
        }
        return res;
    }
    static Mont invMont(const Mont& a) { return pow(a, (ll)Mod - 2); }
    Mont& operator+=(const Mont& o) { return v += o.v, v = v >= Mod ? v - Mod : v, *this; }
    Mont& operator-=(const Mont& o) { return v = v < o.v ? v + Mod : v, v -= o.v, *this; }
    Mont& operator*=(const Mont& o) { return v = reduce((u128)v * o.v), *this; }
    Mont& operator/=(const Mont& o) { return *this *= invMont(o); }
    friend constexpr auto operator+(Mont a, const auto& b) noexcept { return a += b; }
    friend constexpr auto operator-(Mont a, const auto& b) noexcept { return a -= b; }
    friend constexpr auto operator*(Mont a, const auto& b) noexcept { return a *= b; }
    friend constexpr auto operator/(Mont a, const auto& b) noexcept { return a /= b; }
    int get() const {
        u64 x = reduce(v);
        return (int)(x >= Mod ? x - Mod : x);
    }
};

int inv2, inv6;
Mont dujiao(ll n, auto Sg, auto Sh, auto& mp, int a[]) {
    if (n < N) return a[n];
    if (mp.find(n) != mp.end()) return mp[n];
    Mont res = Sh(n);
    for (ll l = 2, r; l <= n; l = r + 1) {
        ll t = n / l;
        r = n / t;
        res -= (Sg(r) - Sg(l - 1)) * dujiao(t, Sg, Sh, mp, a);
    }
    mp[n] = res;
    return res;
}

Mont sg(ll x) {
    Mont n = x;
    return n * (n + 1) * (2 * n + 1) * inv6;
}
Mont sh(ll x) {
    Mont n = x, s = n * (n + 1) * inv2;
    return s * s;
}
gp_hash_table<ll, Mont> mp;

Mont sumn(int l, int r) { return dujiao(r, sg, sh, mp, a) - dujiao(l - 1, sg, sh, mp, a); }
void work() {
    cin >> m >> n;
    euler(N - 1);
    rep(i, 1, N - 1)(a[i] = a[i - 1] + phi[i] * i % m * i % m) %= m;
    inv2 = invp(2, m), inv6 = invp(6, m);
    Mont::init(m);
    Mont ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        Mont x = l, y = n / l;
        Mont su = (1 + y) * y * inv2;
        ans += sumn(l, r) * su * su;
    }
    pt(ans.get());
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (ti == 0) cin >> ti;
    while (ti--) work();
    return 0;
}