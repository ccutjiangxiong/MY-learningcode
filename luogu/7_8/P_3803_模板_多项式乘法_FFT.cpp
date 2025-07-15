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
template <const int mod>
struct modInt {
    modInt(const int x = 0) : num((x % mod + mod) % mod) {}
    explicit operator int() { return num; }
    static constexpr int phi_v = mod - 1;
    static modInt fastPow(modInt a, int b) {
        if (b < 0) return fastPow(inv(a), -b);
        b = b % (phi_v);
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
    static modInt sqrt(const modInt& n) {
        if (n.num == 0) return 0;
        if (n.pow((mod - 1) / 2) != 1) return -1;
        int S = 0, q = mod - 1;
        while (!(q & 1)) q >>= 1, ++S;
        modInt z = 2;
        while (z.pow((mod - 1) / 2) != modInt(mod - 1)) ++z;
        modInt c = z.pow(q);
        modInt x = n.pow((q + 1) / 2);
        modInt t = n.pow(q);
        int M = S;
        while (t != 1) {
            int i = 1;
            modInt tt = t * t;
            while (tt != 1) tt = tt * tt, ++i;
            modInt b = c.pow(1LL << (M - i - 1));
            x *= b, c = b * b;
            t *= c, M = i;
        }
        modInt r1 = x, r2 = -x;
        return r1 < r2 ? r1 : r2;
    }
    static modInt inv(const modInt x) { return fastPow(x, mod - 2); }
    friend std::ostream& operator<<(std::ostream& ou, const modInt& x) { return ou << x.num, ou; }
    friend std::istream& operator>>(std::istream& in, modInt& x) { return in >> x.num, in; }
    constexpr modInt& operator-=(const modInt& o) noexcept {
        return (num -= o.num - mod) %= mod, *this;
    }
    constexpr modInt& operator+=(const modInt& o) noexcept { return (num += o.num) %= mod, *this; }
    constexpr modInt& operator*=(const modInt& o) noexcept { return (num *= o.num) %= mod, *this; }
    constexpr modInt& operator/=(const modInt& o) noexcept { return *this *= inv(o); }
    friend constexpr modInt operator^(modInt a, int e) noexcept { return fastPow(a, e); }
    constexpr modInt operator-() const noexcept { return modInt(0) - *this; }
    friend constexpr auto operator<=>(const modInt& a, const modInt& b) noexcept = default;
    constexpr modInt& operator++() noexcept { return *this += 1; }
    constexpr modInt& operator--() noexcept { return *this -= 1; }
    friend constexpr auto operator+(modInt a, const auto& b) noexcept { return a += b; }
    friend constexpr auto operator-(modInt a, const auto& b) noexcept { return a -= b; }
    friend constexpr auto operator*(modInt a, const auto& b) noexcept { return a *= b; }
    friend constexpr auto operator/(modInt a, const auto& b) noexcept { return a /= b; }
    int num;
};
const int MOD = 998244353;
using mint = modInt<MOD>;
using vmi = vector<mint>;
const int p = 998244353, g = 3, gi = 332748118;
static int NTT_n = 0, NTT_logn = 0;
static vi R;
static vector<vmi> wn[2];
void NTT(vmi& a, int op) {
    int n = a.size();
    if (n != NTT_n) {
        NTT_n = n, NTT_logn = lbt(n), R.assign(n, 0);
        rep(i, 0, n - 1) R[i] = R[i >> 1] >> 1 | (i & 1 ? n >> 1 : 0);
        for (int t = 0; t < 2; t++) {
            wn[t].assign(NTT_logn + 1, {});
            for (int k = 1; k <= NTT_logn; k++) {
                int len = 1 << k, half = len >> 1;
                mint b = mint(t == 0 ? g : gi).pow((p - 1) / len);
                auto& w = wn[t][k];
                w.resize(half), w[0] = 1;
                rep(i, 1, half - 1) w[i] = w[i - 1] * b;
            }
        }
    }
    rep(i, 0, n - 1) if (i < R[i]) swap(a[i], a[R[i]]);
    for (int k = 1, len = 2; k <= NTT_logn; k++, len <<= 1) {
        int half = len >> 1;
        auto& w = wn[op == 1 ? 0 : 1][k];
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < half; j++) {
                mint u = a[i + j];
                mint v = a[i + j + half] * w[j];
                a[i + j] = u + v;
                a[i + j + half] = u - v;
            }
    }
    if (op == -1) {
        mint inv_n = mint::inv(n);
        for (auto& x : a) x *= inv_n;
    }
}

class Poly {
   public:
    vmi a;
    Poly() = default;
    Poly(vmi v) : a(std::move(v)) { normalize(); }
    void normalize() {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }
    int deg() const { return (int)a.size() - 1; }

    // make this public
    static vmi multiply_ntt(vmi A, vmi B) {
        int n = A.size(), m = B.size();
        if (n == 0 || m == 0) return {};
        int sz = 1;
        while (sz < n + m - 1) sz <<= 1;
        A.resize(sz), B.resize(sz);
        NTT(A, 1), NTT(B, 1);
        rep(i, 0, sz - 1) A[i] *= B[i];
        NTT(A, -1), A.resize(n + m - 1);
        return A;
    }

    // make this public
    Poly operator*(const Poly& b) const { return Poly(multiply_ntt(a, b.a)); }

    // allow C[i] syntax
    mint operator[](int idx) const { return (idx >= 0 && idx < (int)a.size()) ? a[idx] : mint(0); }
};
void work() {
    int n, m;
    cin >> n >> m;
    vector<mint> f(n + 1), g(m + 1);
    for (int i = 0; i <= n; ++i) cin >> f[i];
    for (int j = 0; j <= m; ++j) cin >> g[j];
    Poly A(f), B(g), C = A * B;
    int sz = n + m;
    for (int i = 0; i <= sz; ++i) {
        cout << C[i] << (i == sz ? '\n' : ' ');
    }
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