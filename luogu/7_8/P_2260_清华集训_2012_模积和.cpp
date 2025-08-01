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
// const int p = 19940417;
int isp[N], pri[N], phi[N], mu[N], cnt = 0;
void euler(int n) {
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!isp[i]) pri[++cnt] = i, phi[i] = i - 1, mu[i] = -1;
        for (int j = 1; j <= cnt && i * pri[j] <= n; j++) {
            isp[i * pri[j]] = 1;
            phi[i * pri[j]] = phi[i] * (pri[j] - (i % pri[j] != 0));
            mu[i * pri[j]] = i % pri[j] ? -mu[i] : 0;
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
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) return a + (x = 1) + (y = 0) - 1;
    int x1, y1;
    int gcd = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - (a / b) * y1;
    return gcd;
}
int invp2(int a, int p) {
    int x = 0, y = 0;
    return exgcd(a, p, x, y) == 1 ? (x % p + p) % p : -1;
}
template <const int mod>
class modInt {
   public:
    modInt(const int x = 0) : num(x % mod) {}
    explicit operator int() { return num; }
    static constexpr int phi() {
        int res = mod, x = mod;
        for (int p = 2; p * p <= x; ++p) {
            if (x % p == 0) {
                while (x % p == 0) x /= p;
                res = res / p * (p - 1);
            }
        }
        if (x > 1) res = res / x * (x - 1);
        return res;
    }
    static constexpr int phi_v = phi();
    static modInt fastPow(modInt a, int b)  // 快速幂，静态函数
    {
        if (b < 0) return fastPow(inv(a), -b);
        b = b % (phi_v) + phi_v;
        modInt res(1);
        for (; b; a = a * a, b >>= 1)
            if (b & 1) res = res * a;
        return res;
    }
    template <typename... Ts>
    modInt pow(Ts... exps) const {
        int e = 1;
        ((e = ((__int128)e * ((exps % phi_v + phi_v) % phi_v)) % phi_v), ...);
        return fastPow(*this, e);
    }
    static modInt inv(const modInt x) { return invp2(x, mod); }
    friend std::ostream& operator<<(std::ostream& ou, const modInt& x) { return ou << x.num, ou; }
    friend std::istream& operator>>(std::istream& in, modInt& x) { return cin >> x.num, in; }
    constexpr modInt& operator-=(const modInt& o) noexcept {
        return (num -= o.num - mod) %= mod, *this;
    }
    constexpr modInt& operator+=(const modInt& o) noexcept { return (num += o.num) %= mod, *this; }
    constexpr modInt& operator*=(const modInt& o) noexcept { return (num *= o.num) %= mod, *this; }
    constexpr modInt& operator/=(const modInt& o) noexcept { return *this *= inv(o); }
    friend constexpr modInt operator+(modInt a, const modInt& b) noexcept { return a += b; }
    friend constexpr modInt operator-(modInt a, const modInt& b) noexcept { return a -= b; }
    friend constexpr modInt operator*(modInt a, const modInt& b) noexcept { return a *= b; }
    friend constexpr modInt operator/(modInt a, const modInt& b) noexcept { return a /= b; }
    friend constexpr modInt operator^(modInt a, int e) noexcept { return fastPow(a, e); }
    constexpr modInt operator-() const noexcept { return modInt(0) - *this; }
    friend constexpr auto operator<=>(const modInt& a, const modInt& b) noexcept = default;
    constexpr modInt& operator++() noexcept { return *this += 1; }
    constexpr modInt& operator--() noexcept { return *this -= 1; }
    friend constexpr modInt operator+(modInt a, int b) noexcept { return a += b; }
    friend constexpr modInt operator-(modInt a, int b) noexcept { return a -= b; }
    friend constexpr modInt operator*(modInt a, int b) noexcept { return a *= b; }
    friend constexpr modInt operator/(modInt a, int b) noexcept { return a /= b; }

    int num;
};
const int MOD = 19940417;
using mint = modInt<MOD>;
using vmi = vector<mint>;
mint cal(int n, int k) {
    // mint res = n * k;
    mint res = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        if (k / l == 0) break;
        r = min(k / (k / l), n);
        res += (k / l) * (r - l + 1) * (r + l) / 2;
    }
    return res;
}
mint su(int l, int r) {
    mint res = mint(1) * (r + 1) * (2 * r + 1) * r - mint(1) * (l - 1) * l * (2 * l - 1);
    res *= 3323403;
    return res;
}
mint cal2(int n, int m) {
    mint res = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = min({n / (n / l), m / (m / l), n});
        res += su(l, r) * (n / l) * (m / l);z
    }
    return res;
}
void work() {
    cin >> n >> m;
    if (n > m) swap(n, m);
    mint ans = (n * n - cal(n, n)) * (m * m - cal(m, m));
    // rep(i, 1, n) ans -= (n % i) * (m % i);
    ans -= mint(1) * n * m * n - m * cal(n, n) - n * cal(n, m);
    // rep(i, 1, n) ans -= i * i * (n / i) * (m / i);
    ans -= cal2(n, m);
    cout << ans << endl;
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